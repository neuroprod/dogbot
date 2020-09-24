//
// Created by kris on 22.07.20.
//

#include "GraphRenderer.h"
#include "cinder/CinderImGui.h"
#include "cinder/gl/gl.h"
using namespace ci;
GraphRenderer::GraphRenderer()
{

    fboWindow.setup("Graphs",true);
}

void GraphRenderer::reg(Graphable * graphable)
{
   
    for(int i =0;i< graphables.size();i++){
        if(graphables[i]->gName ==graphable->gName  )
        {
            graphables.erase(graphables.begin()+i);

        }
    }

    graphables.push_back(graphable);

}
void GraphRenderer::pulse(int i)
{
    pulseData.push_back(i);
    if (pulseData.size() > 500)
    {
        pulseData.pop_front();
    }
}
void GraphRenderer::draw(std::string type)
{
    int activeGraphs =0;
    for(auto g:graphables)
    {
        if(g->gVisible && g->gType ==type)
        {
            activeGraphs ++;
            if(fboWindow.width != g->currentWidth)
            {
                g->drawLegend(fboWindow.width);
            }

        }

    }

    fboWindow.begin(activeGraphs*200);
    if (ImGui::BeginMenuBar())
    {

        if (ImGui::BeginMenu("Items"))

        {

            for(auto g:graphables)
            {
                if(g->gType ==type) ImGui::Checkbox(g->gName.c_str(),&g->gVisible);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    float step = (float) (fboWindow.width -20) / 500.f;
    int pos = 0;
    for (auto rit=pulseData.rbegin(); rit!=pulseData.rend(); ++rit)
    {


        pos++;
        if (*rit != 0)
        {
            if(*rit == 1)
            {

                gl::color(Color::gray(0.3));
            }
            else
                {
                    gl::color(Color::gray(0.1));
                }

            ci::gl::drawLine(vec2(fboWindow.width-10 -step * pos, 10),vec2(fboWindow.width -step * pos-10, fboWindow.height));

        }


    }





    pos =0;

    for(auto g:graphables)
    {
        if(g->gVisible && g->gType ==type)
        {

            g->gDraw(fboWindow.width);
            ci::gl::translate(pos,g->height);
        }
    }
    fboWindow.end();
}