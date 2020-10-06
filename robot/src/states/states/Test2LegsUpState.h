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
    bool canRepeat(){return true;};
    bool canHaveNextState(  STATE nextState){
        if(nextState==STATE::TESTALLLEGSDOWN ||nextState==STATE::TEST2LEGSUP )
        {
         return true;

        }
        return false;
    }
    float height =40.f;
    float timeRise =0.25f;
    float timeStay =1.f;
    ci::Anim<float> Fpos;
    ci::Anim<float> Bpos;
    IKController * ikController;
    BalanceController *balanceController;
    bool done ;
    bool frUp =true;
};



#endif //BOT_TEST2LEGSUPSTATE_H
