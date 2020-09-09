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
#include "balance/BalanceController.h"

class Simulation
{
public:
    Simulation(){}
    void setup();
    void update();
    void draw();
    void drawSimGui();


    IKController ikController;
    ModelRenderer modelRenderer;
    StateController stateController;
    GaitController gaitController;
    PhysicsController physicsController;
    BalanceController balanceController;
    bool isReady =false;
    bool usePhysics =true;
    bool play =true;
    bool step =false;
};


#endif //BOT_SIMULATION_H
