//
// Created by kris on 19.08.20.
//

#ifndef BOT_STEPINPUT_H
#define BOT_STEPINPUT_H


class StepInput
{
public :
    StepInput(){}
    float stepTime =200;
    float stepHeight =60;
    float moveAngle =0;
    float moveLength =80;
    float rotAngle =0;
    float homeZOffset =30;

    void drawGui(bool ownPannel =true) ;



};


#endif //BOT_STEPINPUT_H
