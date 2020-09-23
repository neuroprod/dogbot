//
// Created by kris on 19.08.20.
//

#ifndef BOT_STANDUPSTATE_H
#define BOT_STANDUPSTATE_H

#include "../../ik/IKController.h"
#include "BaseState.h"
#include "cinder/Timeline.h"

class StandupState : public BaseState
{
public:
    STATE state= STATE::STANDUP;
    StandupState(){};
    std::string getName(){return "STANDUP" ;};
    void start();
    void update();
    bool isDone();

    bool hasGui() {return true;};
    void drawGui();

    ci::Anim<float> bodyY;
    ci::Anim<float> bodyX;
    IKController * ikController;
    bool done ;
};


#endif //BOT_STANDUPSTATE_H
