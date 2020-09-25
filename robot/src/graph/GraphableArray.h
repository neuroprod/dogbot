//
// Created by kris on 22.07.20.
//

#ifndef BOT_GRAPHABLEARRAY_H
#define BOT_GRAPHABLEARRAY_H
#include "Graphable.h"
#include <list>
#include <cinder/Font.h>
#include <cinder/gl/Batch.h>
#include <cinder/gl/gl.h>

class GraphableArray: public Graphable
{
public:
    GraphableArray(){}
    void prepGraph(std::string name,std::string type, int length, std::vector<float> scale, std::vector<ci::Color> color, std::vector<std::string> names);
    void addData(std::vector<float> data);
    void gDraw(int width);
    void drawLegend(int width);
    void pauze();
    void play();
    ci::gl::FboRef			mLegendFbo;

    std::list<std::vector<float>> gData;
    std::vector<float> gScale;
    std::vector<ci::Color> gColors;
    std::vector<std::string> gNames;
    int gSize;
    ci::gl::BatchRef rectBatch;
    ci::Font fontL;
    ci::Font fontS;



};


#endif //BOT_GRAPHABLEARRAY_H
