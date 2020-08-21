//
// Created by kris on 20.08.20.
//

#ifndef BOT_LEGCONTROLLER_H
#define BOT_LEGCONTROLLER_H

#include "cinder/app/App.h"
#include "cinder/BSpline.h"
class LegController;
typedef std::shared_ptr<LegController  > LegControllerRef;


class LegController
{
public:
    LegController(){};
    static LegControllerRef create();
    void setup(ci::vec3 pos);
    void setHomePosOffzet(ci::vec3 offset);
    void setNextState();
    void update(float timeNormal);


    void prepStateSwitch();



    int state;

    ci::BSpline3f currentSpline;
    ci::BSpline3f prevSpline;
    ci::BSpline3f nextSpline;
    float  currentLength=0;
    float  prevLength =0;
    float  lengthDif =0;
    float  nextLength =0;
    float  nextLengthDif =0;
    ci::vec3 homePosStart;
    ci::vec3 homePos;

    float stepHeight =50;
    float moveAngle =0;
    float moveLength =0;
    float rotAngle =0;
    float homeZOffset =0;



    ci::vec3 dirStartFalling;

    ci::vec3 targetPos;
    ci::vec3 prevTargetPos;

    bool debug =false;
    void draw();
    std::vector<ci::vec3> drawArray;

};

#endif //BOT_LEGCONTROLLER_H
