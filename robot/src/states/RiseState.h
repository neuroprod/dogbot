//
// Created by kris on 19.08.20.
//

#ifndef BOT_RISESTATE_H
#define BOT_RISESTATE_H

#include "../ik/IKController.h"
#include "BaseState.h"
#include "cinder/Timeline.h"

class RiseState : public BaseState
{
public:
    STATE state= STATE::RISE;
    RiseState(){};
    std::string getName(){return "RISE" ;};
    void start();
    void update();
    bool isDone();

    ci::Anim<float> bodyY;
    ci::Anim<float> bodyX;
    IKController * ikController;
    bool done ;
};


#endif //BOT_RISESTATE_H
