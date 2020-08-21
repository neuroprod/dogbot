//
// Created by kris on 20.08.20.
//
#include "LegController.h"
#include "cinder/gl/gl.h"
using namespace ci;
LegControllerRef LegController::create()
{
    LegControllerRef ref = std::make_shared<LegController>();
    return ref;
}

void LegController::setup(ci::vec3 pos)
{
    targetPos =homePos=homePosStart =pos;
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
void  LegController::update(float timeNormal)
{

    float length = currentSpline.getLength(0, 1);
    float t = length *timeNormal;
    float ti = currentSpline.getTime(t);
    targetPos= currentSpline.getPosition(ti);
    if(debug)
    {
        drawArray.push_back(  targetPos);
        if(drawArray.size()>100)drawArray.erase(drawArray.begin());
    }

}
void  LegController::draw()
{

    gl::begin(GL_LINE_STRIP);

    for (auto const& p: drawArray) {

        gl::vertex(p);

    }
    gl::end();

}