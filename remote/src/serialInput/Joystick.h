//
// Created by kris on 21.09.20.
//

#ifndef REMOTE_JOYSTICK_H
#define REMOTE_JOYSTICK_H

#include <cinder/osc/Osc.h>
#include "cinder/app/App.h"


class Joystick
{

public:
    Joystick(){};
    void setRaw(float lh,float lv,float rh,float rv);
    ci::osc::Message getMessage();
    void drawDebugGui();

    ci::vec2 mRightJoystick;
    ci::vec2 mLeftJoystick;
    bool mLeftJoystickDown = false;
    bool mRightJoystickDown = false;


    float mLh=0;
    float mLv=0;
    float mRh=0;
    float mRv=0;


};

#endif //REMOTE_JOYSTICK_H
