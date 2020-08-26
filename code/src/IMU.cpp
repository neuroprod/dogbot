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
     ZenSetLogLevel(ZenLogLevel_Info);
     g_imuHandle = 0;
     pollingThread = std::thread(&IMU::pollLoop, this);
 }
 ci::vec3   IMU::getEuler() 
 {
     vec3 e;
     dataMutex.lock();
     e = euler;
     dataMutex.unlock();
     return e;
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
         g_terminate = true;
         client.close();
         //  pollingThread.join();

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
         g_terminate = true;
         client.close();
         pollingThread.join();

     }




     auto sensorPair = client.obtainSensor(g_discoveredSensors[0]);
     auto& obtainError = sensorPair.first;
     auto& sensor = sensorPair.second;

     auto imuPair = sensor.getAnyComponentOfType(g_zenSensorType_Imu);
     auto hasImu = true;// imuPair.has_value();
     auto imu = imuPair.value();

     if (!hasImu)
     {
         g_terminate = true;
         client.close();
         pollingThread.join();
         // return ZenError_WrongSensorType;
     }


     g_imuHandle = imu.component().handle;
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


                     dataMutex.unlock();

                     break;
                 }
             }

         }
     }
 }
   