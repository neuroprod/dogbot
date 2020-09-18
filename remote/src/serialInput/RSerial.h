//
// Created by kris on 15.09.20.
//

#ifndef REMOTE_RSERIAL_H
#define REMOTE_RSERIAL_H
#include "cinder/app/App.h"
#include "cinder/Serial.h"
class RSerial
{
public:
    RSerial(){};
    void setup();
    void worker();
    float clampJoystick(float in);
    bool isConnected =false;

    ci::SerialRef mSerial;
    ci::vec2 getRightJoystick();
    ci::vec2 getLeftJoystick();
    bool getLeftJoystickDown();
    bool getRightJoystickDown();
    
    float getBatteryStatus();

    ci::vec2 mRightJoystick;
    ci::vec2 mLeftJoystick;
    bool mLeftJoystickDown =false;
    bool mRightJoystickDown=false;
    
    float mBattery =0;

    std::thread thread;
    std::mutex dataMutex;
};


#endif //REMOTE_RSERIAL_H
