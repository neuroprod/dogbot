//
// Created by kris on 19.08.20.
//

#ifndef BOT_STATECONTROLE_H
#define BOT_STATECONTROLE_H

#include "cinder/app/App.h"
#include "../ik/IKControle.h"
#include "BaseState.h"
#include "NoneState.h"
#include "RiseState.h"
class StateControle
{
public:
    StateControle(){};
    void setup(IKControle * ikControle);
    void update();
    void draw();
    void setNextState();
    bool autoNextState =false;

    STATE state;
    BaseState *currentState;


    NoneState noneState;
    RiseState riseState;


};

#endif //BOT_STATECONTROLE_H
