//
// Created by kris on 21.09.20.
//

#ifndef REMOTE_JOYSTICK_H
#define REMOTE_JOYSTICK_H

#include <cinder/osc/Osc.h>
#include "cinder/app/App.h"
#include "../settings/SettingsHandler.h"

class Joystick
{

public:
    Joystick(){};
    void setRaw(float lh,float lv,float rh,float rv);
    ci::osc::Message getMessage();
    void drawDebugGui();
    float clampJoystick(float in,float min,float max);
    ci::vec2 mRightJoystick;
    ci::vec2 mLeftJoystick;
    bool mLeftJoystickDown = false;
    bool mRightJoystickDown = false;

    Sfloat cLh =SETTINGS()->getFloat("AppSettings","cLh",0);
    Sfloat cLv =SETTINGS()->getFloat("AppSettings","cLv",0);
    Sfloat cRh =SETTINGS()->getFloat("AppSettings","cRh",0);
    Sfloat cRv =SETTINGS()->getFloat("AppSettings","cRv",0);
    float mLh=0;
    float mLv=0;
    float mRh=0;
    float mRv=0;


};

#endif //REMOTE_JOYSTICK_H
