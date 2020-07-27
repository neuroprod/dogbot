//
// Created by kris on 22.07.20.
//

#include "GraphRenderer.h"
#include "cinder/CinderImGui.h"
#include "cinder/gl/gl.h"
void GraphRenderer::reg(Graphable * graphable)
{
    graphables.push_back(graphable);

}
void GraphRenderer::draw()
{
    ImGui::Begin( "graphs" );
    for(auto g:graphables)
    {
        ImGui::Checkbox(g->gName.c_str(),&g->gVisible);
    }
    ImGui::End();
    float pos =0;
    for(auto g:graphables)
    {
        if(g->gVisible)
        {
            ci::gl::translate(0,100);
            g->gDraw();

        }
    }

}