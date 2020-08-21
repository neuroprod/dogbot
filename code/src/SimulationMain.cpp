//
// Created by kris on 22.07.20.
//

#include "SimulationMain.h"

#include "graph/GraphRenderer.h"

using namespace ci;
using namespace ci::app;
void SimulationMain::setup() {
   // ImGui::Initialize();
    setWindowSize(windowSizeX->value(),windowSizeY->value());
    setWindowPos(0,0);
    gaitControle.setup();
    ikControle.setup();
    modelRenderer.setup();
    stateControle.setup(&ikControle ,&gaitControle);

}
void SimulationMain::update() {

    stateControle.update();

    ikControle.update();


    modelRenderer.model->setPosition(ikControle.bodyMatrix,ikControle.angles);



    modelRenderer.update();

}
void SimulationMain::draw() {

    ikControle.drawGui();
    modelRenderer.draw();
    stateControle.draw();
    gaitControle.drawGui();
    GRAPH()->draw();

}