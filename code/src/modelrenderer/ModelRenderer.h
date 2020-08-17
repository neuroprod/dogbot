//
// Created by kris on 17.08.20.
//

#ifndef BOT_MODELRENDERER_H
#define BOT_MODELRENDERER_H
#include "../gui/FBOWindow.h"
#include "cinder/app/App.h"
#include "cinder/CinderImGui.h"
#include "cinder/gl/gl.h"
#include "OrbitCamera.h"
#include "FKModel.h"
class ModelRenderer
{
public:
    ModelRenderer(){};
    void setup();
    void update();
    void draw();
    void drawShadow();
    FBOWindow fboWindow;
    OrbitCamera camera;

    FKModelRef model;

    ci::gl::FboRef			mFbo;
    ci::CameraPersp			mLightCam;
    ci::vec3				mLightPos;

    ci::gl::Texture2dRef	mShadowMapTex;
    int	fboSize = 2048;

};


#endif //BOT_MODELRENDERER_H