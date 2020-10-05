//
// Created by kris on 22.07.20.
//

#include "Simulation.h"
#include "graph/GraphRenderer.h"
#include "communication/Communication.h"

using namespace ci;
using namespace ci::app;

void Simulation::setup()
{

    joystick =std::make_shared<Joystick>();
    gaitController.setup( );
    ikController.setup();
    ikController.update();
    modelRenderer.setup();
    stateController.setup(&ikController, &gaitController,&balanceController);
    physicsController.setup( ikController.bodyMatrix, ikController.angles);
    balanceController.setup(false);
    isReady = true;

}

void Simulation::update()
{
    if(COM()->receiver->hasNewJoystick)
    {
        COM()->receiver->updateJoystick( joystick );

        if(joystick->mLeftJoystickDown ||joystick->mRightJoystickDown )
        {
            //ignore for now
        }else
        {
            gaitController.stepInput.update(joystick);
        }
    }
    if(COM()->receiver->hasNewCommand)
    {
        ivec2 com = COM()->receiver->getCommand();
        stateController.setCommand(com.x,com.y);
    }

    if (!play && !step) return;
    step = false;

    stateController.update();
    if (usePhysics && waitTime<0)
    {

        balanceController.update(physicsController.model.angleX/3.1415f*180.f, physicsController.model.angleZ/3.1415f*180.f,0,0);

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