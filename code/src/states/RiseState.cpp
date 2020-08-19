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
    bodyY = ikControle->bodyY;

    timeline().apply(&bodyY,BOTSETTINGS()->bodyY,1.f,EaseInOutQuad()).finishFn( [&](){done=true;});
};
void RiseState::update()
{
    ikControle->bodyY  =bodyY;
};
bool RiseState::isDone()
{
    return  done;
}