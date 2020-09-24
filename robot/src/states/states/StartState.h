//
// Created by kris on 19.08.20.
//

#ifndef BOT_STARTSTATE_H
#define BOT_STARTSTATE_H

#include "BaseState.h"

class StartState : public BaseState
{
public:
    StartState(){}
    STATE state = STATE::START;
    std::string getName(){return "START" ;};
    void start(){};
    void update(){};
    bool isDone(){
        return true;
    }
    bool canHaveNextState(  STATE nextState){

        if(nextState== STATE::STANDUP)return true;
        return false;
    }


};


#endif //BOT_STARTSTATE_H
