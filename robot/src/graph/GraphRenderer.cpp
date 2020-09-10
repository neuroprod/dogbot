//
// Created by kris on 22.07.20.
//

#include "GraphRenderer.h"
#include "cinder/CinderImGui.h"
#include "cinder/gl/gl.h"

GraphRenderer::GraphRenderer()
{

    fboWindow.setup("Graphs");
}

void GraphRenderer::reg(Graphable * graphable)
{
    graphables.push_back(graphable);

}
void GraphRenderer::draw(std::string type)
{

    fboWindow.begin();
    if (ImGui::BeginMenuBar())
    {

        if (ImGui::BeginMenu("Items"))

        {

            for(auto g:graphables)
            {
                if(g->gType ==type);
                ImGui::Checkbox(g->gName.c_str(),&g->gVisible);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }






    float pos =0;
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