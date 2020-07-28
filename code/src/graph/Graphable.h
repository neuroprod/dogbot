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
    virtual void gDraw() {};
    std::string gName;
    bool gVisible = true;

};
#endif //BOT_GRAPHABLE_H