//
// Created by kris on 20.08.20.
//

#ifndef BOT_GAITCONTROLLER_H
#define BOT_GAITCONTROLLER_H

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include <imgui/imgui.h>
#include <cinder/gl/Fbo.h>
#include "../modelrenderer/OrbitCamera.h"
#include "../input/StepInput.h"
#include "cinder/BSpline.h"
#include "LegController.h"
#include "../modelrenderer/SymbolBatches.h"
class GaitController
{
public:
    GaitController(){};

    void setup();
    void reset();
    void update();
    void drawGui();

    float currentTime;
    double previousTime;
    float currentStepTime;
    float stepTimeTotal;
    bool debug;
    ci::BSpline3f getWalkStep(StepInput &stepInput,LegControllerRef legController);
    ci::BSpline3f getHomeStep(StepInput &stepInput,LegControllerRef legController);
    ci::BSpline3f getHomeRise(StepInput &stepInput,LegControllerRef legController);
    ci::BSpline3f getWalkFall(StepInput &stepInput,LegControllerRef legController);
    std::vector<LegControllerRef> legs;

    /////// gui debug stuff
    StepInput stepInput;


    int leg_combo= 0;
    int leg_combo_current= 0;
    LegControllerRef currentLeg;

    SymbolBatches drawBatches;

    ImVec2 vMin;
    ImVec2 vMax;
    ci::gl::FboRef			mFbo;
    float stepTime =150;
    float stepHeight =20;
    float moveAngle =0;
    float moveLength =0;
    float rotAngle =0;
    float homeZOffset =0;

    OrbitCamera camera;
    float fboWidth =0;
};


#endif //BOT_GAITCONTROLLER_H
