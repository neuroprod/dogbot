//
// Created by kris on 22.07.20.
//

#ifndef BOT_GRAPHABLE_H
#define BOT_GRAPHABLE_H
#include "cinder/app/App.h"

class Graphable;
typedef std::shared_ptr<Graphable> GraphableRef;

class Graphable
{
public:
    Graphable() {};
    virtual void gDraw(int width) {};
    std::string gName;
    std::string gType;
    int height =200;
    bool gVisible = false;
bool drawZero = false;
};
#endif //BOT_GRAPHABLE_H
