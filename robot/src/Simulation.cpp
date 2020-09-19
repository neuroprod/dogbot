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
    balanceController.setup(false);
    isReady = true;

}

void Simulation::update()
{
    if (!play && !step) return;
    step = false;

    stateController.update();
    if (usePhysics && waitTime<0)
    {

        balanceController.update(physicsController.model.angleX, physicsController.model.angleZ);

        ikController.setBalance(balanceController.offsetX,balanceController.offsetZ);

    }
    if (usePhysics && waitTime>0)
    {
        waitTime-= 1.f/120.f;
    }
    ikController.update();


    if (usePhysics)
    {
        physicsController.model.setMotorTargets( ikController.angles);
        physicsController.update();
        modelRenderer.model->setPosition(physicsController.model.bodyMatrix, physicsController.model.angles);
        modelRenderer.physicsPositions = physicsController.model.positions;


    } else
    {
        modelRenderer.model->setPosition(ikController.bodyMatrix, ikController.angles);
    }


    modelRenderer.update();


}

void Simulation::draw()
{
    drawSimGui();
    balanceController.drawGui();
    physicsController.drawGui();
    ikController.drawGui();
    modelRenderer.draw();
    stateController.draw();
    gaitController.drawGui();
    GRAPH()->draw("simulation");

}

void Simulation::drawSimGui()
{
    ImGui::Begin("Simulation");
    if(ImGui::Checkbox("use physics", &usePhysics)){waitTime=3;}
    if (ImGui::Button("reset"))
    {

        ikController.reset();
        ikController.update();
        physicsController.reset();
        stateController.reset();
        balanceController.reset();
        waitTime =3;
    }
    if (ImGui::Button("play")) { play = true; } ImGui::SameLine();
    if (ImGui::Button("pauze")) { play = false; }ImGui::SameLine();
    if (ImGui::Button("step")) { step = true; };

    ImGui::End();

}