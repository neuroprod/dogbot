//
// Created by kris on 19.08.20.
//

#ifndef BOT_STEPSTATE_H
#define BOT_STEPSTATE_H


#include "../ik/IKController.h"
#include "BaseState.h"
#include "cinder/Timeline.h"
#include "../walking/GaitController.h"

class StepState : public BaseState
{
public:
    STATE state= STATE::STEP;
    StepState(){};
    std::string getName(){return "STEP" ;};
    void start();
    void update();
    bool isDone();



    IKController * ikController;
    GaitController * gaitController;
    bool done ;
};


#endif //BOT_STEPSTATE_H
