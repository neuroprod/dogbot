//
// Created by kris on 19.08.20.
//

#include "StepState.h"


#include "../../RobotSettings.h"
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
    float scale =1;
    if(!gaitController->frUp)scale=-1;

    ikController->setBalance(balanceController->balanceX, balanceController->balanceZ*scale);
}
bool StepState::isDone()
{
    return   !gaitController->isWalking;
}
void StepState::drawGui(){

    ImGui::Text("-> GaitController panel");

}