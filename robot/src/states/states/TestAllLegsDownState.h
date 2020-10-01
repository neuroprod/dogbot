//
// Created by kris on 01.10.20.
//

#ifndef BOT_TESTALLLEGSDOWNSTATE_H
#define BOT_TESTALLLEGSDOWNSTATE_H




#include "../../ik/IKController.h"
#include "BaseState.h"
#include "cinder/Timeline.h"
#include "../../settings/SettingsHandler.h"
class TestAllLegsDownState : public BaseState
{
public:

    TestAllLegsDownState (){ state= STATE::TESTALLLEGSDOWN;};
    std::string getName(){return "TESTALLLEGSDOWN" ;};
    void start();
    void update();
    bool isDone();

    bool hasGui() {return false;};
    void drawGui();

    bool canHaveNextState(  STATE nextState){

        return true;
    }



    ci::Anim<float> FRpos;
    ci::Anim<float> BLpos;
    ci::Anim<float> FLpos;
    ci::Anim<float> BRpos;
    IKController * ikController;
    bool done ;
};



#endif //BOT_TESTALLLEGSDOWNSTATE_H
