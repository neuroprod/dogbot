//
// Created by kris on 19.08.20.
//

#ifndef BOT_STEPINPUT_H
#define BOT_STEPINPUT_H


class StepInput
{
public :
    StepInput(){}
    float stepTime =150;
    float stepHeight =30;
    float moveAngle =0;
    float moveLength =0;
    float rotAngle =0;
    float homeZOffset =30;

    void drawGui(bool ownPannel =true) ;



};


#endif //BOT_STEPINPUT_H