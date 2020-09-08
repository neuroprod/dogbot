//
// Created by kris on 19.08.20.
//

#include "StepState.h"


#include "../RobotSettings.h"
using namespace ci;
using namespace ci::app;
void StepState::start()
{
    done =false;
    gaitController->reset();
}
void StepState::update()
{
    gaitController->update();
    for(int i=0;i<4;i++)
    {
        ikController->legs[i]->targetPos =  gaitController->legs[i]->targetPos;
    }

}
bool StepState::isDone()
{
    return  done;
}
