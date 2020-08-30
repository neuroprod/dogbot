//
// Created by kris on 20.08.20.
//
#include "LegController.h"
#include "cinder/gl/gl.h"
#include "../modelrenderer/SymbolBatches.h"
using namespace ci;
using namespace ci::app;
using namespace std;
LegControllerRef LegController::create()
{
    LegControllerRef ref = std::make_shared<LegController>();
    return ref;
}

void LegController::setup(ci::vec3 pos)
{

    targetPos =homePos=homePosStart =pos;
    prevTargetPos = targetPos;
}

void  LegController::setNextState(){
    state ++;
    if (state>3)state =0;
};
void LegController::setHomePosOffzet(ci::vec3 offset)
{
    if(homePosStart.z>1)offset.z*=-1;
    homePos =homePosStart+offset;
}
void LegController::prepStateSwitch()
{
   currentLength = currentSpline.getLength(0,1);
    //goUpHome
    if(state ==0){
        if(prevSpline.getNumControlPoints()<2)
        {
            prevLength = 0;
        }else
            {
                prevLength =  prevSpline.getLength(0,1);
            }


        lengthDif =  currentLength-prevLength;
    }
    if(state ==1){

        prevLength =  prevSpline.getLength(0,1);
        lengthDif =  currentLength-prevLength;

        nextLength =  nextSpline.getLength(0,1);
        nextLengthDif = currentLength-nextLength;
    }
}
void  LegController::update(float timeNormal)
{
    prevTargetPos = targetPos;



    if(state==0 )
    {

        float t =  prevLength * timeNormal+  lengthDif *(timeNormal*timeNormal);

        float ti = currentSpline.getTime(t);
        targetPos = currentSpline.getPosition(ti);
    }
    else if(state==1 )
    {
        float Tinv =1.0-timeNormal;
        float t =   nextLength* Tinv+  nextLengthDif *(Tinv*Tinv);

        float ti = currentSpline.getTime(currentLength -t);

        targetPos = currentSpline.getPosition(ti);
    }
   else
    {

        float t =  currentLength * timeNormal;
        float ti = currentSpline.getTime(t);

        targetPos = currentSpline.getPosition(ti);
    }



    if(debug)
    {
        drawArray.push_back(  targetPos);
        if(drawArray.size()>100)drawArray.erase(drawArray.begin());
    }

}
void  LegController::draw()
{

    gl::begin(GL_LINE_STRIP);
    gl::color(0.5,0.5,0.5);
    for (auto const& p: drawArray) {


        gl::vertex(p);

    }
    gl::end();
    gl::color(1,1,1);
    gl::pushMatrices();
    gl::translate(targetPos);
    gl::scale(vec3(2.f));
    SYMBOLBATCHES()->sphereBatch->draw();
    gl::popMatrices();

    int  s = drawArray.size();
    if(s>50)
    {
        for (int i =0; i < 50; i++)
        {
            gl::pushMatrices();
            gl::translate(drawArray[s-1-i]);
            gl::scale(vec3(2.f-(float)i/25.f));
            SYMBOLBATCHES()->sphereBatch->draw();
           // gl::drawSphere(drawArray[s-1-i],2.f-(float)i/25.f);

            gl::popMatrices();

        }
    }
}