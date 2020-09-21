//
// Created by kris on 21.09.20.
//

#ifndef REMOTE_JOYSTICK_H
#define REMOTE_JOYSTICK_H

#include <cinder/osc/Osc.h>
#include "cinder/app/App.h"


struct Joystick
{
    ci::vec2 mRightJoystick;
    ci::vec2 mLeftJoystick;
    bool mLeftJoystickDown = false;
    bool mRightJoystickDown = false;

    ci::osc::Message getMessage()
    {
    ci::osc::Message msg("/joystick");
    msg.append( mLeftJoystick.x );
    msg.append( mLeftJoystick.y );
    msg.append( mLeftJoystickDown );
    msg.append( mRightJoystick.x );
    msg.append( mRightJoystick.y );
    msg.append( mRightJoystickDown );
    return msg;
    }
};
#endif //REMOTE_JOYSTICK_H
