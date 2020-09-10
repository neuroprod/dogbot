//
// Created by kris on 19.08.20.
//

#include "RiseState.h"
#include "../RobotSettings.h"
using namespace ci;
using namespace ci::app;
void RiseState::start()
{
    done =false;
    //ikControle->lockUI();
    bodyY = ikController->bodyY;
    bodyX = ikController->bodyX;
    timeline().apply(&bodyX,40.f,0.7f,EaseInOutQuad()).delay(0.3);
    timeline().apply(&bodyY,BOTSETTINGS()->bodyY,1.f,EaseInOutQuad()).finishFn( [&](){done=true;}).delay(0);
};
void RiseState::update()
{
    ikController->bodyY  =bodyY;
    ikController->bodyX  =bodyX;
};
bool RiseState::isDone()
{
    return  done;
}