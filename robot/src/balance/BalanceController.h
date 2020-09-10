//
// Created by kris on 09.09.20.
//

#ifndef BOT_BALANCECONTROLLER_H
#define BOT_BALANCECONTROLLER_H
#include "PID.h"
#include "../graph/GraphableArray.h"

class BalanceController
{
public:
    BalanceController(){};
    void setup(bool isRobot );
    void drawGui();
    void update(float rotX,float rotZ);
    PID pidX;
    PID pidZ;
    float offsetX =0;
    float offsetZ =0;
    GraphableArray balanceGraph;
};


#endif //BOT_BALANCECONTROLLER_H
