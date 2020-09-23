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


    bool rDown = false;
    if (rv > 900)rDown = true;

    bool lDown = false;
    if (lv > 900)lDown = true;

    float xl = clampJoystick((lh -cLh->value())*-1 ,0,0);
    float yl = clampJoystick(lv -cLv->value() ,0,0);


    float xr = clampJoystick((rh -cRh->value())*-1 ,0,0);
    float yr = clampJoystick(rv -cRv->value() ,0,0);





    mRightJoystick.x = xr;
    mRightJoystick.y = yr;
    mLeftJoystick.x = xl;
    mLeftJoystick.y = yl;
    mLeftJoystickDown = lDown;
    mRightJoystickDown = rDown;





}
float Joystick::clampJoystick(float in,float min,float max)
{
    return in;

}
void Joystick::drawDebugGui()
{

    ImGui::Text("raw input: ");
    ImGui::Text("Lhor:%f  Lver:%f  Rhor:%f  Rver:%f", mLh, mLv, mRh, mRv);

    if(ImGui::Button("save settings"))
    {
        SETTINGS()->save();
    }
    if(ImGui::Button("set center"))
    {
        cLh->setValue(mLh);
        cLv->setValue(mLv);
        cRh->setValue(mRh);
        cRv->setValue(mRv);
    }

    ImGui::Text("output: ");
    ImGui::Text("Lhor:%f  Lver:%f  Rhor:%f  Rver:%f", mLeftJoystick.x ,mLeftJoystick.y,     mRightJoystick.x,  mRightJoystick.y);
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