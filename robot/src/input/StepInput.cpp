//
// Created by kris on 19.08.20.
//

#include <imgui/imgui.h>
#include "StepInput.h"

using namespace ci;
using namespace ci::app;
using namespace std;

void StepInput::update(JoystickRef joystick)
{
    if(!useJoystick)return;
    const float PI = 3.14159265359;
    vec2 p = joystick->mLeftJoystick;
    if (p.x != 0 || p.y != 0)
    {
        vec2 pn = glm::normalize(p);
        moveAngle = atan2(-pn.y, pn.x) +  PI/2;
        if (moveAngle > PI)moveAngle -= 2 * PI;
        if (moveAngle < -PI)moveAngle += 2 * PI;
        float factor = powf(pn.y,4.f);
    //    console()<<factor<<" "<<pn.y<<endl;
        p.y  *=factor;
        p.x *= 0.2;
        moveLength = glm::length(p) * 1;

    } else
    {
        moveAngle = 0;
        moveLength = 0;
    }
    rotAngle = joystick->mRightJoystick.x * 0.f / 180.f * PI;

}

void StepInput::drawGui(bool ownPannel)
{
    if (ownPannel)ImGui::Begin("StepInput");

    ImGui::Checkbox("use remote",&useJoystick);
    ImGui::SliderFloat("moveLength", &moveLength, 0, 300);
    if(ImGui::Button("testMove"))
    {

        if(test)
        {
            moveLength=0;
        }else{
                moveLength=1;
            }
        test =!test;
    }
    ImGui::SliderAngle("angleMove", &moveAngle, -180, 180);
    ImGui::SliderAngle("rotate", &rotAngle, -10, 10);
    ImGui::Separator();

    ImGui::SliderFloat("stepTime", &stepTime, 100, 2000);
    ImGui::SliderFloat("stepHeight", &stepHeight, 0, 200);
    ImGui::SliderFloat("homeZOffset", &homeZOffset, 0, 50);
    if (ownPannel) ImGui::End();


}