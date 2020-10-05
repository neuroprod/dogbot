//
// Created by kris on 01.10.20.
//

#include "Test2LegsUpState.h"
#include "cinder/CinderImGui.h"

using namespace ci;
using namespace ci::app;
void Test2LegsUpState::start()
{
    //  GRAPH()->play();
    done =false;

    FRpos =  ikController->FR->targetPos.y;
    BLpos = ikController->BL->targetPos.y;

    timeline().apply(&FRpos,height,time,EaseInOutQuad()) ;
    timeline().appendTo(&FRpos,0.f,time,EaseInOutQuad());

    timeline().apply(&BLpos,height,time,EaseInOutQuad());
    timeline().appendTo(&BLpos,0.0f,time,EaseInOutQuad()).finishFn( [&](){done=true;});




};
void Test2LegsUpState::update()
{
    ikController->FR->targetPos.y =FRpos;
    ikController->BL->targetPos.y =BLpos;
    ikController->setBalance(balanceController->balanceX, balanceController->balanceZ);

};
bool Test2LegsUpState::isDone()
{

    return  done;
}

void Test2LegsUpState::drawGui(){

    ImGui::SliderFloat("height",&height,0.f,80.f);

}