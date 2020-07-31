//
// Created by kris on 22.07.20.
//

#ifndef BOT_ROBOTMAIN_H
#define BOT_ROBOTMAIN_H
#include "cinder/app/App.h"
#include "motor/MotorControl.h"
#include "settings/BotSettings.h"
class RobotMain
{
public:
    RobotMain(){};
    void setup();
    void update();
    void draw();

    Sint windowSizeX=SETTINGS()->getInt("RobotSettings","windowSizeX",1920);
    Sint windowSizeY=SETTINGS()->getInt("RobotSettings","windowSizeY",1080);
    MotorControl motorControl;
};


#endif //BOT_ROBOTMAIN_H
