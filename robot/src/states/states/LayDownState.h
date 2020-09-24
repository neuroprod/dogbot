//
// Created by kris on 23.09.20.
//

#ifndef BOT_LAYDOWNSTATE_H
#define BOT_LAYDOWNSTATE_H
#include "../../ik/IKController.h"
#include "BaseState.h"
#include "../../settings/SettingsHandler.h"
#include "cinder/Timeline.h"
class LayDownState : public BaseState
{
public:
    LayDownState(){
        state = STATE::LAYDOWN;
    }

   std::string getName(){return "LAYDOWN" ;} ;
    void start();
    void update();
    bool isDone();

    void drawGui();
    bool hasGui() {return true;};
    bool canHaveNextState(  STATE nextState){
        if(nextState ==STATE::STANDUP){ return true;}
        return false;
    }
    bool done =false;
    Sfloat layDownTime = SETTINGS()->getFloat("RobotSettings","layDownTime",2);
    ci::Anim<float> bodyY;
    ci::Anim<float> bodyX;
    IKController * ikController;


};

#endif //BOT_LAYDOWNSTATE_H
