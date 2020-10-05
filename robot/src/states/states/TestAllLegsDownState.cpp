//
// Created by kris on 01.10.20.
//

#include "TestAllLegsDownState.h"
#include "cinder/CinderImGui.h"

using namespace ci;
using namespace ci::app;
void TestAllLegsDownState::start()
{
    //  GRAPH()->play();
    done =false;

    FRpos =  ikController->FR->targetPos.y;
    BLpos = ikController->BL->targetPos.y;
    FLpos =  ikController->FL->targetPos.y;
    BRpos = ikController->BR->targetPos.y;
    float time =0.5;
    offsetZ= ikController->mOffsetZ;
    offsetX= ikController->mOffsetX;
    timeline().apply(&offsetZ,0.f,time,EaseInOutQuad());
    timeline().apply(&offsetX,0.f,time,EaseInOutQuad());
    timeline().apply(&FRpos,0.f,time,EaseInOutQuad());
    timeline().apply(&FLpos,0.f,time,EaseInOutQuad());
    timeline().apply(&BRpos,0.f,time,EaseInOutQuad());
    timeline().apply(&BLpos,0.f,time,EaseInOutQuad()).finishFn( [&](){done=true;});

};
void TestAllLegsDownState::update()
{
    ikController->FR->targetPos.y =FRpos;
    ikController->FL->targetPos.y =FLpos;
    ikController->BL->targetPos.y =BLpos;
    ikController->BR->targetPos.y =BRpos;
    ikController->setBalance(offsetX.value(),offsetZ.value());
    if(done) balanceController->setLevel();
};
bool TestAllLegsDownState::isDone()
{
    // if(done)GRAPH()->pauze();
    return  done;
}

void TestAllLegsDownState::drawGui(){



}