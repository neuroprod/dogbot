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
#include "../graph/GraphableArray.h"
#include "../input/Joystick.h"

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
    bool editGate =false;
    ci::BSpline3f getWalkStep(StepInput &stepInput,LegControllerRef legController);
    ci::BSpline3f getHomeStep(StepInput &stepInput,LegControllerRef legController);
    ci::BSpline3f getHomeRise(StepInput &stepInput,LegControllerRef legController);
    ci::BSpline3f getWalkFall(StepInput &stepInput,LegControllerRef legController);
    std::vector<LegControllerRef> legs;
    float walkRisingIn = 0.1;
    float walkRisingOut = 0.4;
    float walkRisingMidX = 0.1;
    float  walkRisingMidY = 0.6;

    float walkFalingIn = 0.32;
    float walkFalingOut = 0.04;
    float walkFalingMidX = 0.82;
    float  walkFalingMidY = 0.89;

    float delta;
    /////// gui debug stuff
    StepInput stepInput;
    GraphableArray gaitGraph;

    int leg_combo= 0;
    int leg_combo_current= 0;
    LegControllerRef currentLeg;



    ImVec2 vMin;
    ImVec2 vMax;
    ci::gl::FboRef			mFbo;


    OrbitCamera camera;
    float fboWidth =0;
bool isWalking =false;
    bool frUp =false;

};


#endif //BOT_GAITCONTROLLER_H
