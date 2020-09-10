//
// Created by kris on 22.07.20.
//

#include "GraphableArray.h"
#include "cinder/gl/gl.h"
using namespace ci;
using namespace ci::app;
using namespace std;

void GraphableArray::prepGraph(std::string name,string type, int size, std::vector<float> scale, std::vector<ci::Color> color, std::vector<std::string> names)
{
    gName = name;
    gType = type;

    gScale = scale;
    gColors = color;
    gNames = names;

    gSize = size;


   fontL = Font(loadAsset("fonts/Ubuntu-M.ttf"),20);
    fontS = Font(loadAsset("fonts/Ubuntu-M.ttf"),16);
    rectBatch= gl::Batch::create(geom::Rect(Rectf(0,0,15,15)), gl::getStockShader(gl::ShaderDef().color()));
}
void GraphableArray::addData(std::vector<float> _data){
    gData.push_back(_data);
    if (gData.size() > 500)
    {
        gData.pop_front();
    }

}
void GraphableArray::gDraw(int width){


    gl::pushMatrices();
    gl::translate(0, 100);
    gl::color(Color::gray(0.2));
    gl::drawLine(vec2(0,0),vec2(width,0));
   gl::drawString(gName, vec2(10, -90), Color(1, 1, 1), fontL);
   float step = (float)(width-10)/500.f;
    for (int i = 0; i < gSize; i++) {
        gl::color(gColors[i]);
        gl::pushMatrices();
        gl::translate(10,-90+ 30+i*20);

       gl::drawString(gNames[i] , vec2(22,0),    Color(1,1,1), fontS);
        rectBatch->draw();
        gl::popMatrices();

        gl::begin(GL_LINE_STRIP);
       float pos = 0;
        for (auto const& val : gData) {

            gl::vertex(vec2(pos, -val[i] * gScale[i]));
            pos +=  step;
        }
        gl::end();


    }

    gl::popMatrices();


}

