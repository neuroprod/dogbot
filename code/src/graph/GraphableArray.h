//
// Created by kris on 22.07.20.
//

#ifndef BOT_GRAPHABLEARRAY_H
#define BOT_GRAPHABLEARRAY_H
#include "Graphable.h"
#include <list>
class GraphableArray: public Graphable
{
public:
    GraphableArray(){}
    void prepGraph(std::string name, int length, std::vector<float> scale, std::vector<ci::Color> color, std::vector<std::string> names);
    void addData(std::vector<float> data);
    void gDraw();

    std::list<std::vector<float>> gData;
    std::vector<float> gScale;
    std::vector<ci::Color> gColors;
    std::vector<std::string> gNames;
    int gSize;
};


#endif //BOT_GRAPHABLEARRAY_H
