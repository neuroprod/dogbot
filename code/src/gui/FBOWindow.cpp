//
// Created by kris on 12.08.20.
//
#include "cinder/CinderImGui.h"
#include "FBOWindow.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Fbo.h"

using namespace ci;
using namespace ci::app;

void FBOWindow::setup(std::string name)
{

    mName = name;

};

void FBOWindow::begin()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGuiWindowFlags window_flags = 0;

    window_flags |= ImGuiWindowFlags_MenuBar;
    ImGui::Begin(mName.c_str(), __null, window_flags);
    ImVec2 vMin = ImGui::GetWindowContentRegionMin();
    ImVec2 vMax = ImGui::GetWindowContentRegionMax();

    int widthNew = vMax.x - vMin.x;
    int heightNew = vMax.y - vMin.y;

    if (widthNew != width  || heightNew != height )
    {
        needResize = true;
        width  =widthNew;
        height =heightNew;


    }
    if (needResize)
    {
        gl::Fbo::Format format;
        format.setSamples( 4 );
        mFbo = gl::Fbo::create(  width-2, height-2, format.depthTexture() );
    }

     mFbo->bindFramebuffer();
    // clear out the FBO with blue
    gl::clear( Color( 0.0, 0.0f, 0.0f ) );

    // setup the viewport to match the dimensions of the FBO
    gl::viewport( ivec2( 0 ), mFbo->getSize() );
    gl::setMatricesWindow(mFbo->getSize(),true);

};

void FBOWindow::end()
{
    mFbo->unbindFramebuffer();

     ImVec2 uv_min = ImVec2(0.0f, 1.0f);                 // Top-left
   ImVec2 uv_max = ImVec2(1.0f, 0.0f);                 // Lower-right
   ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
   ImVec4 border_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // 50% opaque white
   ImGui::Image( (void*)(intptr_t)mFbo->getColorTexture()->getId(), ImVec2(width, height), uv_min, uv_max, tint_col, border_col);
   ImGui::End();
   ImGui::PopStyleVar();
   needResize =false;
};