//
// Created by kris on 21.09.20.
//

#ifndef REMOTE_JOYSTICK_H
#define REMOTE_JOYSTICK_H

#include <cinder/osc/Osc.h>
#include "cinder/app/App.h"
class Joystick;
typedef std::shared_ptr<Joystick> JoystickRef;
class Joystick
{
public:
    Joystick(){};
    ci::vec2 mRightJoystick;
    ci::vec2 mLeftJoystick;
    bool mLeftJoystickDown = false;
    bool mRightJoystickDown = false;


};
#endif //REMOTE_JOYSTICK_H
