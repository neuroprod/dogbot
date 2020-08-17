//
// Created by kris on 12.08.20.
//

#ifndef BOT_FBOWINDOW_H
#define BOT_FBOWINDOW_H
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Fbo.h"
#include "cinder/CinderImGui.h"
class FBOWindow
{
public:
    FBOWindow(){};
    void setup(std::string name);
    bool begin();
    void end();
    int width=0;
    int height=0;
    bool needResize =true;

    std::string mName;
    ImVec2 vMin;
    ImVec2 vMax;
    ci::gl::FboRef			mFbo;
};


#endif //BOT_TEXTUREWINDOW_H
