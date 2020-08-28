//
// Created by kris on 22.07.20.
//

#ifndef BOT_SIMULATION_H
#define BOT_SIMULATION_H

#include "cinder/app/App.h"
#include "settings/SettingsHandler.h"
#include "graph/GraphableArray.h"
#include "modelrenderer/ModelRenderer.h"
#include "ik/IKController.h"
#include "states/StateController.h"
#include "input/StepInput.h"
#include "walking/GaitController.h"
#include "physics/PhysicsController.h"
class Simulation
{
public:
    Simulation(){}
    void setup();
    void update();
    void draw();



    IKController ikController;
    ModelRenderer modelRenderer;
    StateController stateController;
    GaitController gaitController;
    PhysicsController physicsController;

    bool isReady =false;
};


#endif //BOT_SIMULATION_H
