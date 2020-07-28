//
// Created by kris on 22.07.20.
//

#ifndef BOT_ROBOTMAIN_H
#define BOT_ROBOTMAIN_H
#include "cinder/app/App.h"
#include "motor/MotorControl.h"
class RobotMain
{
public:
    RobotMain(){};
    void setup();
    void update();
    void draw();

    MotorControl motorControl;
};


#endif //BOT_ROBOTMAIN_H
