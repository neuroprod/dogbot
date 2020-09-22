//
// Created by kris on 19.08.20.
//

#include <imgui/imgui.h>
#include "StepInput.h"

void StepInput::update(JoystickRef joystick)
{

    rotAngle = joystick->mRightJoystick.x *10.f/180.f*3.1415;

}
void StepInput::drawGui(bool ownPannel )
{
    if(ownPannel)ImGui::Begin("StepInput");

    ImGui::SliderFloat("moveLength",&moveLength,0,300);
    ImGui::SliderAngle("angleMove",&moveAngle,-180,180);
    ImGui::SliderAngle("rotate",&rotAngle,-10,10);
    ImGui::Separator();

    ImGui::SliderFloat("stepTime",&stepTime,100,2000);
    ImGui::SliderFloat("stepHeight",&stepHeight,0,200);
    ImGui::SliderFloat("homeZOffset",&homeZOffset,0,50);
    if(ownPannel) ImGui::End();


}