//
// Created by kris on 19.08.20.
//

#include "StandupState.h"
#include "../../RobotSettings.h"
#include "cinder/CinderImGui.h"
using namespace ci;
using namespace ci::app;
void StandupState::start()
{
    done =false;

    bodyY = ikController->bodyY;
    bodyX = ikController->bodyX;
    timeline().apply(&bodyX,40.f,0.7f,EaseInOutQuad()).delay(0.3);
    timeline().apply(&bodyY,BOTSETTINGS()->bodyY,1.f,EaseInOutQuad()).finishFn( [&](){done=true;}).delay(0);
};
void StandupState::update()
{
    ikController->bodyY  =bodyY;
    ikController->bodyX  =bodyX;
};
bool StandupState::isDone()
{
    return  done;
}

void StandupState::drawGui(){

    ImGui::Text("test");

}