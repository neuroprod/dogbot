#include <imgui/imgui.h>
#include "IMU.h"
using namespace zen;
using namespace std;
using namespace ci;
using namespace ci::app;
 IMU::IMU()
{
     

}

 void  IMU::start() 
 {
     ZenSetLogLevel(ZenLogLevel_Warning);
     g_imuHandle = 0;
     pollingThread = std::thread(&IMU::pollLoop, this);
 }
 ci::vec3  IMU::getEuler()
 {
     vec3 e;
     dataMutex.lock();
     e = euler;
     dataMutex.unlock();
     return e;
 }
ci::vec3   IMU::getLinearAccel()
{
    vec3 e;
    dataMutex.lock();
    e = linearAcc;
    dataMutex.unlock();
    return e;
}
void IMU::drawGui()
{
     vec3 e =getEuler();
     vec3 a =getLinearAccel();
     ImGui::Begin("IMU");
ImGui::InputFloat3("angle",&e[0]);
    ImGui::InputFloat3("l",&a[0]);
        ImGui::End();
}
 void IMU::addDiscoveredSensor(const ZenEventData_SensorFound& desc)
 {
    
     g_discoveredSensors.push_back(desc);
 }

 void  IMU::pollLoop()
 {
     std::pair<ZenError, zen::ZenClient> clientPair = make_client();

     auto& clientError = clientPair.first;
     auto& client = clientPair.second;

     if (clientError) {}

     if (auto error = client.listSensorsAsync())
     {
         console()<<"IMU FAILED: 1"<<endl;
         client.close();
         std::terminate();


     }
     bool nComplete = true;
     while (nComplete)
     {
         const auto pair = client.waitForNextEvent();
         const bool success = pair.has_value();
         auto& event = pair.value();
         if (!success)
             break;

         if (!event.component.handle)
         {
             switch (event.eventType)
             {
             case ZenSensorEvent_SensorFound:
                 addDiscoveredSensor(event.data.sensorFound);
                 break;

             case ZenSensorEvent_SensorListingProgress:
                 if (event.data.sensorListingProgress.progress == 1.0f)
                     nComplete = false;
                 break;
             }
         }
     }


     if (g_discoveredSensors.empty())
     {
         console()<<"IMU FAILED: 2"<<endl;
         client.close();
         std::terminate();


     }




     auto sensorPair = client.obtainSensor(g_discoveredSensors[0]);
     auto& obtainError = sensorPair.first;
     auto& sensor = sensorPair.second;

     auto imuPair = sensor.getAnyComponentOfType(g_zenSensorType_Imu);
     auto hasImu =  imuPair.has_value();


     if (!hasImu)
     {
         console()<<"IMU FAILED: 3"<<endl;
         client.close();
         g_terminate =true;

     }else
     {
         auto imu = imuPair.value();


         g_imuHandle = imu.component().handle;
         console() << "IMU OK" << endl;
     }
     while (!g_terminate)
     {
         unsigned int i = 0;
         while (true)
         {
             const auto pair = client.waitForNextEvent();
             const bool success = pair.has_value();
             auto& event = pair.value();
             if (!success)
                 break;

             if (!event.component.handle)
             {
                 switch (event.eventType)
                 {
                 case ZenSensorEvent_SensorFound:
                     addDiscoveredSensor(event.data.sensorFound);
                     break;

                 case ZenSensorEvent_SensorListingProgress:
                     if (event.data.sensorListingProgress.progress == 1.0f)
                         g_discoverCv.notify_one();
                     break;
                 }
             }
             else if ((g_imuHandle > 0) && (event.component.handle == g_imuHandle))
             {
                 switch (event.eventType)
                 {
                 case ZenImuEvent_Sample:
                     dataMutex.lock();
                     euler.x = event.data.imuData.r[0];
                     euler.y = event.data.imuData.r[1];
                     euler.z = event.data.imuData.r[2];
                     linearAcc.x  =event.data.imuData.linAcc[0];
                     linearAcc.y  =event.data.imuData.linAcc[1];
                     linearAcc.z  =event.data.imuData.linAcc[2];

                     dataMutex.unlock();

                     break;
                 }
             }

         }
     }
 }
   