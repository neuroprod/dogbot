//
// Created by kris on 22.07.20.
//

#include "GraphableArray.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

void GraphableArray::prepGraph(std::string name, string type, int size, std::vector<float> scale,
                               std::vector<ci::Color> color, std::vector<std::string> names)
{
    gName = name;
    gType = type;

    gScale = scale;
    gColors = color;
    gNames = names;

    gSize = size;


    fontL = Font(loadAsset("fonts/Ubuntu-M.ttf"), 20);
    fontS = Font(loadAsset("fonts/Ubuntu-M.ttf"), 16);
    rectBatch = gl::Batch::create(geom::Rect(Rectf(0, 0, 15, 15)), gl::getStockShader(gl::ShaderDef().color()));


}

void GraphableArray::drawLegend(int width)
{

    if (width == 0)return;
    currentWidth = width;
    gl::Fbo::Format format;
    //format.setSamples( 16 );

    mLegendFbo = gl::Fbo::create(currentWidth, height, format.depthTexture());


    mLegendFbo->bindFramebuffer();


    gl::viewport(ivec2(0), mLegendFbo->getSize());
    gl::setMatricesWindow(mLegendFbo->getSize(), true);
    gl::clear(Color(0, 0.0f, 0.0f));

    gl::pushMatrices();


    gl::draw(mLegendFbo->getColorTexture());
    gl::translate(0, 100);
    gl::color(Color::gray(0.2));
    gl::drawLine(vec2(0, 0), vec2(currentWidth, 0));
    gl::drawString(gName, vec2(10, -90), Color(1, 1, 1), fontL);

    for (int i = 0; i < gSize; i++)
    {
        gl::color(gColors[i]);
        gl::pushMatrices();
        gl::translate(10, -90 + 30 + i * 20);

        gl::drawString(gNames[i], vec2(22, 0), Color(1, 1, 1), fontS);
        rectBatch->draw();
        gl::popMatrices();


    }

    gl::popMatrices();

    mLegendFbo->unbindFramebuffer();

}

void GraphableArray::pauze()
{ isPauze = true; };

void GraphableArray::play()
{ isPauze = false; };

void GraphableArray::addData(std::vector<float> _data)
{
    if (isPauze) return;
    if (gData.size() >= 500)
    {
        return;
    }
    gData.push_back(_data);
    if (gData.size() > 500)
    {
        gData.pop_front();
    }

}

void GraphableArray::gDraw(int width)
{


    gl::pushMatrices();
    if (mLegendFbo)
    {
        gl::color(Color::gray(1));
        gl::draw(mLegendFbo->getColorTexture());
    }
    gl::translate(0, 100);
    //  gl::color(Color::gray(0.2));
    // gl::drawLine(vec2(0,0),vec2(width,0));
    //gl::drawString(gName, vec2(10, -90), Color(1, 1, 1), fontL);
    float step = (float) (width - 20) / 500.f;
    for (int i = 0; i < gSize; i++)
    {
        gl::color(gColors[i]);
        //  gl::pushMatrices();
        //   gl::translate(10,-90+ 30+i*20);

        // gl::drawString(gNames[i] , vec2(22,0),    Color(1,1,1), fontS);
        // rectBatch->draw();
        //gl::popMatrices();

        gl::begin(GL_LINE_STRIP);
        float pos = 0;

        for (auto rit = gData.rbegin(); rit != gData.rend(); ++rit)
        {

            gl::vertex(vec2(width - pos - 10, (*rit)[i] * gScale[i]));
            pos += step;


        }


        gl::end();


    }

    gl::popMatrices();


}

