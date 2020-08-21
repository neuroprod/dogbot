//
// Created by kris on 19.08.20.
//

#ifndef BOT_STATECONTROLLER_H
#define BOT_STATECONTROLLER_H

#include "cinder/app/App.h"
#include "../ik/IKController.h"
#include "../walking/GaitController.h"
#include "BaseState.h"
#include "NoneState.h"
#include "RiseState.h"
#include "StepState.h"
class StateController
{
public:
    StateController(){};
    void setup(IKController * ikController,GaitController *gaitController);
    void update();
    void draw();
    void setNextState();
    bool autoNextState =true;

    STATE state;
    BaseState *currentState;


    NoneState noneState;
    RiseState riseState;
    StepState stepState;

};

#endif //BOT_STATECONTROLLER_H
