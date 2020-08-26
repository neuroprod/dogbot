//
// Created by kris on 22.07.20.
//

#include "SimulationMain.h"

#include "graph/GraphRenderer.h"

using namespace ci;
using namespace ci::app;
void SimulationMain::setup() {

    gaitController.setup();
    ikController.setup();
    modelRenderer.setup();
    stateController.setup(&ikController ,&gaitController);
    physicsController.setup();



}
void SimulationMain::update() {

    stateController.update();
    ikController.update();

    physicsController.update();


    modelRenderer.model->setPosition(ikController.bodyMatrix,ikController.angles);



    modelRenderer.update();

}
void SimulationMain::draw() {

    physicsController.drawGui();
    ikController.drawGui();
    modelRenderer.draw();
    stateController.draw();
    gaitController.drawGui();
    GRAPH()->draw();

}