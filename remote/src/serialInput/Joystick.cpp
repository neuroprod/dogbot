//
// Created by kris on 23.09.20.
//

#include "Joystick.h"
#include "cinder/CinderImGui.h"
void Joystick::setRaw(float lh, float lv, float rh, float rv)
{

    mLh = lh;
    mLv = lv;
    mRh = rh;
    mRv = rv;


    /*bool rDown = false;
    if (i2 > 900)rDown = true;

    bool lDown = false;
    if (i3 > 900)lDown = true;

    float xl = clampJoystick(i1 - 515.f)*-1;
    float yl = clampJoystick((i2 - 512.f) * -1.f);


    float xr = clampJoystick(i4 - 505.f)*-1;
    float yr = clampJoystick((i3 - 515.f) * -1.f);


    std::lock_guard<std::mutex> lock(dataMutex);


    joystick.mRightJoystick.x = xr;
    joystick.mRightJoystick.y = yr;
    joystick.mLeftJoystick.x = xl;
    joystick.mLeftJoystick.y = yl;
    joystick.mLeftJoystickDown = lDown;
    joystick.mRightJoystickDown = rDown;*/





}

void Joystick::drawDebugGui()
{

    ImGui::Text("raw input: ");
    ImGui::Text("Lhor:%f  Lver:%f  Rhor:%f  Rver:%f", mLh, mLv, mRh, mRv);

}

ci::osc::Message Joystick::getMessage()
{
    ci::osc::Message msg("/joystick");
    msg.append(mLeftJoystick.x);
    msg.append(mLeftJoystick.y);
    msg.append(mLeftJoystickDown);
    msg.append(mRightJoystick.x);
    msg.append(mRightJoystick.y);
    msg.append(mRightJoystickDown);
    return msg;
}