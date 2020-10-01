//
// Created by kris on 01.10.20.
//

#ifndef BOT_TEST2LEGSUPSTATE_H
#define BOT_TEST2LEGSUPSTATE_H



#include "../../ik/IKController.h"
#include "BaseState.h"
#include "cinder/Timeline.h"
#include "../../settings/SettingsHandler.h"
#include "../../balance/BalanceController.h"

class Test2LegsUpState : public BaseState
{
public:

    Test2LegsUpState (){ state= STATE::TEST2LEGSUP;};
    std::string getName(){return "TEST2LEGSUP" ;};
    void start();
    void update();
    bool isDone();

    bool hasGui() {return true;};
    void drawGui();

    bool canHaveNextState(  STATE nextState){
        if(nextState==STATE::TESTALLLEGSDOWN)
        {
        return true;

        }
        return false;
    }
    float height =30;


    ci::Anim<float> FRpos;
    ci::Anim<float> BLpos;
    IKController * ikController;
    BalanceController *balanceController;
    bool done ;
};



#endif //BOT_TEST2LEGSUPSTATE_H
