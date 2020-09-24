//
// Created by kris on 24.09.20.
//


#include "LayDownState.h"
#include "../../RobotSettings.h"
#include "cinder/CinderImGui.h"
using namespace ci;
using namespace ci::app;
void LayDownState::start()
{
    done =false;
    float time = layDownTime->value();
    bodyY = ikController->bodyY;
    bodyX = ikController->bodyX;
    timeline().apply(&bodyX,BOTSETTINGS()->bodyXStart,0.7f*time,EaseInOutQuad()).delay(0.3*time);
    timeline().apply(&bodyY,BOTSETTINGS()->bodyYStart,time,EaseInOutQuad()).finishFn( [&](){done=true;}).delay(0);
};
void LayDownState::update()
{
    ikController->bodyY  =bodyY;
    ikController->bodyX  =bodyX;
};
bool LayDownState::isDone()
{
    return  done;
}

void LayDownState::drawGui(){

    ImGui::SliderFloat("time",&layDownTime->value(),1.f,5.f);

}