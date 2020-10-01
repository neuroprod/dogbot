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
    float time =3;
    float height =30;
    timeline().apply(&FRpos,height,time,EaseInOutQuad());
    timeline().apply(&BLpos,height,time,EaseInOutQuad()).finishFn( [&](){done=true;});

};
void Test2LegsUpState::update()
{
    ikController->FR->targetPos.y =FRpos;
    ikController->BL->targetPos.y =BLpos;


};
bool Test2LegsUpState::isDone()
{
    // if(done)GRAPH()->pauze();
    return  done;
}

void Test2LegsUpState::drawGui(){

    ImGui::SliderFloat("height",&height,0.f,80.f);

}