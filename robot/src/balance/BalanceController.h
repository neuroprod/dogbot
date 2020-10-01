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
    float inputX =0;
    float inputZ =0;
    float balanceZ =0;
    float balanceX =0;
    GraphableArray balanceGraph;
    void reset();
    void setLevel();
};


#endif //BOT_BALANCECONTROLLER_H
