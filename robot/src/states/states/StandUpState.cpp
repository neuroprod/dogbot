//
// Created by kris on 19.08.20.
//

#include "StandUpState.h"
#include "../../RobotSettings.h"
#include "cinder/CinderImGui.h"
#include "../../graph/GraphRenderer.h"
using namespace ci;
using namespace ci::app;
void StandUpState::start()
{

    done =false;
    float time = standUpTime->value();
    bodyY = ikController->bodyY;
    bodyX = ikController->bodyX;
    timeline().apply(&bodyX,BOTSETTINGS()->bodyX,0.5f*time,EaseInOutQuad()).delay(0.5*time);
    timeline().apply(&bodyY,BOTSETTINGS()->bodyY,time,EaseInOutQuad()).finishFn( [&](){done=true;}).delay(0);

};
void StandUpState::update()
{
    
    ikController->bodyY  =bodyY;
    ikController->bodyX  =bodyX;


};
bool StandUpState::isDone()
{

    return  done;
}

void StandUpState::drawGui(){

    ImGui::SliderFloat("time",&standUpTime->value(),1.f,5.f);

}