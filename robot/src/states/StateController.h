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
#include "states/StandupState.h"
#include "states/StepState.h"
#include "states/LaydownState.h"
class StateController
{
public:
    StateController(){};
    void setup(IKController * ikController,GaitController *gaitController);
    void setCommand(int type,int com);
    void update();
    void draw();
    void reset();
    void setNewState(std::shared_ptr<BaseState> state);

    std::vector<std::shared_ptr<BaseState>> states;

    STATE state;
    std::shared_ptr<BaseState> currentState;


    std::shared_ptr<StartState> sitState;
    std::shared_ptr<StandupState> standupState;
    std::shared_ptr<StepState> stepState;
    std::shared_ptr<LaydownState> laydownState;

};

#endif //BOT_STATECONTROLLER_H
