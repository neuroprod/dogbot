//
// Created by kris on 19.08.20.
//

#ifndef BOT_BASESTATE_H
#define BOT_BASESTATE_H
#include "../StateEnum.h"
#include "cinder/app/App.h"
#include "cinder/CinderImGui.h"
class BaseState
{
public:
    BaseState(){};

    STATE state= STATE::BASE;
    std::string name ="BASE";
    bool showGui =false;
    virtual bool hasGui() {return false;};
    virtual void drawGui(){};
    virtual void start(){};
    virtual void update(){};
    virtual bool isDone(){};
    std::string  virtual getName()=0;
};


#endif //BOT_BASESTATE_H
