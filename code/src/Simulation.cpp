//
// Created by kris on 22.07.20.
//

#include "Simulation.h"

#include "graph/GraphRenderer.h"

using namespace ci;
using namespace ci::app;

void Simulation::setup()
{

    gaitController.setup();
    ikController.setup();
    ikController.update();
    modelRenderer.setup();
    stateController.setup(&ikController, &gaitController);
    physicsController.setup( ikController.bodyMatrix, ikController.angles);

    isReady = true;

}

void Simulation::update()
{

    stateController.update();
    ikController.update();


    if (usePhysics)
    {
        physicsController.model.setMotorTargets( ikController.angles);
        physicsController.update();
        modelRenderer.model->setPosition(physicsController.model.bodyMatrix, physicsController.model.angles);
    } else
    {
        modelRenderer.model->setPosition(ikController.bodyMatrix, ikController.angles);
    }


    modelRenderer.update();

}

void Simulation::draw()
{
    drawSimGui();
    physicsController.drawGui();
    ikController.drawGui();
    modelRenderer.draw();
    stateController.draw();
    gaitController.drawGui();
    GRAPH()->draw();

}

void Simulation::drawSimGui()
{
    ImGui::Begin("Simulation");
    ImGui::Checkbox("use physics", &usePhysics);
    if (ImGui::Button("reset"))
    {
        ikController.reset();
        ikController.update();
        physicsController.reset();
        stateController.reset();

    }


    ImGui::End();

}