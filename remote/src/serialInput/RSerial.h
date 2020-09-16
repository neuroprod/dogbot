//
// Created by kris on 15.09.20.
//

#ifndef REMOTE_RSERIAL_H
#define REMOTE_RSERIAL_H
#include "cinder/app/App.h"

class RSerial
{
public:
    RSerial(){};
    void setup();
    void worker();
    ci::vec2 getRightJoystick();
    ci::vec2 getLeftJoystick();
    float getBatteryStatus();

    ci::vec2 mRightJoyStick;
    ci::vec2 mLeftJoyStick;
    float mBattery =0;

    std::thread thread;
    std::mutex dataMutex;
};


#endif //REMOTE_RSERIAL_H
