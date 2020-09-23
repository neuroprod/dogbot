//
// Created by kris on 23.09.20.
//

#ifndef BOT_LAYDOWNSTATE_H
#define BOT_LAYDOWNSTATE_H
#include "BaseState.h"

class LaydownState : public BaseState
{
public:
    LaydownState(){}
    STATE state = STATE::LAYDOWN;
   std::string getName(){return "LAYDOWN" ;} ;
    void start(){};
    void update(){};
    bool isDone(){ return true; }
    bool hasGui() {return true;};
    void drawGui(){
        ImGui::Text("todo");
    }
    ci::Anim<float> bodyY;
    ci::Anim<float> bodyX;
    IKController * ikController;


};

#endif //BOT_LAYDOWNSTATE_H
