//
// Created by kris on 01.10.20.
//

#include "Test2LegsUpState.h"
#include "cinder/CinderImGui.h"

using namespace ci;
using namespace ci::app;

void Test2LegsUpState::start()
{

    done = false;
    if (frUp)
    {
        Fpos = ikController->FR->targetPos.y;
        Bpos = ikController->BL->targetPos.y;


    } else
    {

        Fpos = ikController->FL->targetPos.y;
        Bpos = ikController->BR->targetPos.y;
    }

    timeline().apply(&Fpos, height, timeRise, EaseInOutQuad());
    timeline().appendTo(&Fpos, 0.f, timeRise, EaseInOutQuad()).delay(timeStay);

    timeline().apply(&Bpos, height, timeRise, EaseInOutQuad());
    timeline().appendTo(&Bpos, 0.0f, timeRise, EaseInOutQuad()).finishFn([&]()
                                                                     { done = true; }).delay(timeStay);
    frUp = !frUp;
};

void Test2LegsUpState::update()
{
    float scale =1.f;
    if (frUp)
    {

        ikController->FR->targetPos.y = Fpos;
        ikController->BL->targetPos.y = Bpos;
    } else
    {
        ikController->FL->targetPos.y = Fpos;
        ikController->BR->targetPos.y = Bpos;
        scale =-1.f;
    }
    ikController->setBalance(balanceController->balanceX, balanceController->balanceZ);

};

bool Test2LegsUpState::isDone()
{

    return done;
}

void Test2LegsUpState::drawGui()
{

    ImGui::SliderFloat("height", &height, 0.f, 80.f);
    ImGui::SliderFloat("timeRise", &timeRise, 0.f, 2.f);
    ImGui::SliderFloat("timeStay", &timeStay, 0.f, 10.f);
}