//
// Created by kris on 19.08.20.
//

#ifndef BOT_STANDUPSTATE_H
#define BOT_STANDUPSTATE_H

#include "../../ik/IKController.h"
#include "BaseState.h"
#include "cinder/Timeline.h"
#include "../../settings/SettingsHandler.h"
class StandUpState : public BaseState
{
public:

    StandUpState(){ state= STATE::STANDUP;};
    std::string getName(){return "STANDUP" ;};
    void start();
    void update();
    bool isDone();

    bool hasGui() {return true;};
    void drawGui();

    bool canHaveNextState(  STATE nextState){return true;}

    Sfloat standUpTime = SETTINGS()->getFloat("RobotSettings","standUpTime",3);

    ci::Anim<float> bodyY;
    ci::Anim<float> bodyX;
    IKController * ikController;
    bool done ;
};


#endif //BOT_STANDUPSTATE_H
