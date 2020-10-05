#include <imgui/imgui.h>
#include "IMU.h"
#include "../Status.h"

using namespace zen;
using namespace std;
using namespace ci;
using namespace ci::app;

IMU::IMU()
{


}

void IMU::start()
{
    ZenSetLogLevel(ZenLogLevel_Warning);
    g_imuHandle = 0;
    pollingThread = std::thread(&IMU::pollLoop, this);
}
ci::vec3 IMU::getEuler()
{
    vec3 e;
    dataMutex.lock();
    e = euler;
    dataMutex.unlock();
    return e;

}
ci::vec3 IMU::getAngularVel()
{
    vec3 e;
     dataMutex.lock();
     e = angularVel;
     dataMutex.unlock();
    return e;
}

glm::quat IMU::getQuat()
{
    glm::quat q;
    dataMutex.lock();
    q = quaternion;
    dataMutex.unlock();
    return q;
}

ci::vec3 IMU::getLinearAccel()
{
    vec3 e;
    dataMutex.lock();
    e = linearAcc;
    dataMutex.unlock();
    return e;
}

void IMU::drawGui()
{

    vec3 a = getLinearAccel();
    glm::quat q = getQuat();
    ImGui::Begin("IMU");
    ImGui::InputFloat4("quat", &q[0]);
    ImGui::InputFloat3("linearAcc", &a[0]);
    ImGui::InputFloat3("linearAcc", &a[0]);
    ImGui::End();
}

void IMU::addDiscoveredSensor(const ZenEventData_SensorFound &desc)
{

    g_discoveredSensors.push_back(desc);
}

void IMU::pollLoop()
{
    std::pair<ZenError, zen::ZenClient> clientPair = make_client();

    auto &clientError = clientPair.first;
    auto &client = clientPair.second;

    if (clientError)
    {}

    if (auto error = client.listSensorsAsync())
    {

        STATUS()->logError("IMU FAILED: 1",true);
        client.close();
        std::terminate();


    }
    bool nComplete = true;
    while (nComplete)
    {
        const auto pair = client.waitForNextEvent();
        const bool success = pair.has_value();
        auto &event = pair.value();
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
        STATUS()->logError("IMU FAILED: 2",true);
        client.close();
        g_terminate = true;


    }


    auto sensorPair = client.obtainSensor(g_discoveredSensors[0]);
    auto &obtainError = sensorPair.first;
    auto &sensor = sensorPair.second;

    auto imuPair = sensor.getAnyComponentOfType(g_zenSensorType_Imu);
    auto hasImu = imuPair.has_value();


    if (!hasImu)
    {
        STATUS()->logError("IMU FAILED: 3",true);
        client.close();
        g_terminate = true;

    } else
    {
        auto imu = imuPair.value();


        g_imuHandle = imu.component().handle;

    }
    while (!g_terminate)
    {
        unsigned int i = 0;
        while (true)
        {
            const auto pair = client.waitForNextEvent();
            const bool success = pair.has_value();
            auto &event = pair.value();
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
            } else if ((g_imuHandle > 0) && (event.component.handle == g_imuHandle))
            {
                switch (event.eventType)
                {
                    case ZenImuEvent_Sample:
                        dataMutex.lock();


                        quaternion.y = event.data.imuData.q[0];
                        quaternion.z = event.data.imuData.q[1];
                        quaternion.x = event.data.imuData.q[2];
                        quaternion.w = event.data.imuData.q[3];


                        angularVel.x = event.data.imuData.w[0];
                        angularVel.y = event.data.imuData.w[1];
                        angularVel.z = event.data.imuData.w[2];

                        euler.x = event.data.imuData.r[0];
                        euler.y = event.data.imuData.r[1];
                        euler.z = event.data.imuData.r[2];


                        linearAcc.x = event.data.imuData.linAcc[0];
                        linearAcc.y = event.data.imuData.linAcc[1];
                        linearAcc.z = event.data.imuData.linAcc[2];

                        dataMutex.unlock();

                        break;
                }
            }

        }
    }
}
   