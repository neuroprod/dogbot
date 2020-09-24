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
    virtual void drawLegend(int width) {};
    virtual void gDraw(int width) {};
    std::string gName;
    std::string gType;
    int height =200;
    bool gVisible = false;
    bool drawZero = false;
    int currentWidth=-1;
};
#endif //BOT_GRAPHABLE_H
