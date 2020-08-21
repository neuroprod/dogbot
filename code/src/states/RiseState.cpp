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

    timeline().apply(&bodyY,BOTSETTINGS()->bodyY,2.f,EaseInOutQuad()).finishFn( [&](){done=true;}).delay(2);
};
void RiseState::update()
{
    ikController->bodyY  =bodyY;
};
bool RiseState::isDone()
{
    return  done;
}