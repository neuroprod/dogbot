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

    Sfloat minLh =SETTINGS()->getFloat("AppSettings","minLh",255);
    Sfloat minLv =SETTINGS()->getFloat("AppSettings","minLv",268);
    Sfloat minRh =SETTINGS()->getFloat("AppSettings","minRh",263);
    Sfloat minRv =SETTINGS()->getFloat("AppSettings","minRv",267);

    Sfloat maxLh =SETTINGS()->getFloat("AppSettings","maxLh",264);
    Sfloat maxLv =SETTINGS()->getFloat("AppSettings","maxLv",265);
    Sfloat maxRh =SETTINGS()->getFloat("AppSettings","maxRh",252);
    Sfloat maxRv =SETTINGS()->getFloat("AppSettings","maxRv",285);

    float mLh=0;
    float mLv=0;
    float mRh=0;
    float mRv=0;

    bool testMinMax =false;
};

#endif //REMOTE_JOYSTICK_H
