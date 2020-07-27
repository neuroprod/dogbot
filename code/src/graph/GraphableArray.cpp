//
// Created by kris on 22.07.20.
//

#include "GraphableArray.h"
#include "cinder/gl/gl.h"
using namespace ci;
using namespace ci::app;
using namespace std;

void GraphableArray::prepGraph(std::string name, int size, std::vector<float> scale, std::vector<ci::Color> color, std::vector<std::string> names)
{
    gScale = scale;
    gColors = color;
    gNames = names;
    gName = name;
    gSize = size;


}
void GraphableArray::addData(std::vector<float> _data){
    gData.push_back(_data);
    if (gData.size() > 500)
    {
        gData.pop_front();
    }

}
void GraphableArray::gDraw(){


    gl::pushMatrices();
    gl::translate(100, 100);
    gl::drawStringRight(gName, vec2(0, -90), Color(1, 1, 1), Font("Arial",30));

    for (int i = 0; i < gSize; i++) {

        gl::drawStringRight(gNames[i] , vec2(0,-90+ 30+i*20), gColors[i], Font("Arial", 24));
        gl::color(gColors[i]);
        gl::begin(GL_LINE_STRIP);
        int pos = 0;
        for (auto const& val : gData) {

            gl::vertex(vec2(pos, val[i] * gScale[i]));
            pos += 2;
        }
        gl::end();


    }

    gl::popMatrices();


}

