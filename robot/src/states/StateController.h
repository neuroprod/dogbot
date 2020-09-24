//
// Created by kris on 19.08.20.
//

#ifndef BOT_STATECONTROLLER_H
#define BOT_STATECONTROLLER_H

#include "cinder/app/App.h"
#include "../ik/IKController.h"
#include "../walking/GaitController.h"
#include "states/BaseState.h"
#include "states/StartState.h"
#include "states/StandUpState.h"
#include "states/StepState.h"
#include "states/LayDownState.h"
class StateController
{
public:
    StateController(){};
    void setup(IKController * ikController,GaitController *gaitController);
    void setCommand(int type,int com);
    void update();
    void draw();
    void reset();
    void trySetNewState(STATE state);

    std::vector<std::shared_ptr<BaseState>> states;

    STATE state;
    std::shared_ptr<BaseState> currentState;


    std::shared_ptr<StartState> sitState;
    std::shared_ptr<StandUpState> standupState;
    std::shared_ptr<StepState> stepState;
    std::shared_ptr<LayDownState> laydownState;

};

#endif //BOT_STATECONTROLLER_H
