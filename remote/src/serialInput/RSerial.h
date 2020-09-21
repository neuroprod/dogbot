//
// Created by kris on 15.09.20.
//

#ifndef REMOTE_RSERIAL_H
#define REMOTE_RSERIAL_H
#include "cinder/app/App.h"
#include "cinder/Serial.h"
#include "Joystick.h"

class RSerial
{
public:
    RSerial(){};
    void setup();
    void worker();
    float clampJoystick(float in);
    bool isConnected =false;

    ci::SerialRef mSerial;
    Joystick  getJoystick();

    
    float getBatteryStatus();
    Joystick joystick;

    
    float mBattery =0;

    std::thread thread;
    std::mutex dataMutex;
};


#endif //REMOTE_RSERIAL_H
