//
// Created by kris on 19.08.20.
//

#ifndef BOT_STATECONTROLLER_H
#define BOT_STATECONTROLLER_H

#include "cinder/app/App.h"
#include "../ik/IKController.h"
#include "../walking/GaitController.h"
#include "../balance/BalanceController.h"
#include "states/BaseState.h"
#include "states/StartState.h"
#include "states/StandUpState.h"
#include "states/StepState.h"
#include "states/LayDownState.h"
#include "states/Test2LegsUpState.h"
#include "states/TestAllLegsDownState.h"

class StateController
{
public:
    StateController(){};
    void setup(IKController * ikController,GaitController *gaitController,BalanceController *balanceController);
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
    std::shared_ptr<Test2LegsUpState> test2LegsUpState;
    std::shared_ptr<TestAllLegsDownState> testAllLegsDownState;
};

#endif //BOT_STATECONTROLLER_H
