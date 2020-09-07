//
// Created by kris on 19.08.20.
//

#ifndef BOT_NONESTATE_H
#define BOT_NONESTATE_H

#include "BaseState.h"

class NoneState : public BaseState
{
public:
    NoneState(){}
    STATE state = STATE::NONE;
    std::string getName(){return "NONE" ;};
    void start(){};
    void update(){};
    bool isDone()
    { return true; }



};


#endif //BOT_NONESTATE_H
