#pragma once
#include <OpenZen.h>

#include "cinder/app/App.h"
class IMU
{
    void pollLoop();
    void addDiscoveredSensor(const ZenEventData_SensorFound& desc);

   ci::vec3 euler;
    glm::quat quaternion;
    ci::vec3 linearAcc;
    ci::vec3 angularVel;
    std::mutex dataMutex;

    std::mutex g_discoverMutex;
    std::vector<ZenSensorDesc> g_discoveredSensors;
    std::condition_variable g_discoverCv;

    std::atomic_bool g_terminate = false;


    std::atomic<uintptr_t> g_imuHandle;

    std::thread pollingThread;
public:
    IMU();
    void start();
    void drawGui();

    glm::quat getQuat();
    ci::vec3 getEuler();
    ci::vec3 getLinearAccel();
    ci::vec3 getAngularVel();
};

