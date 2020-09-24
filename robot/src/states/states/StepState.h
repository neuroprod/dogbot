//
// Created by kris on 19.08.20.
//

#ifndef BOT_STEPSTATE_H
#define BOT_STEPSTATE_H


#include "../../ik/IKController.h"
#include "BaseState.h"
#include "cinder/Timeline.h"
#include "../../walking/GaitController.h"

class StepState : public BaseState
{
public:

    StepState(){state= STATE::STEP;};
    std::string getName(){return "STEP" ;};
    void start();
    void update();
    bool isDone();
    bool hasGui() {return true;};
    void drawGui();
    bool canHaveNextState(  STATE nextState){
        if(nextState ==STATE::STANDUP){ return false;}

        return true;
    }
    IKController * ikController;
    GaitController * gaitController;
    bool done ;
};


#endif //BOT_STEPSTATE_H
