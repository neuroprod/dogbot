//
// Created by kris on 22.07.20.
//

#include "Robot.h"

#include "cinder/CinderImGui.h"
#include "graph/GraphRenderer.h"
using namespace ci;
using namespace ci::app;
using namespace std;

void Robot::setup() {


    gaitController.setup();

    imu.start();
    ikController.setup();
    modelRenderer.setup();
    modelRenderer.showMesh =false;
    modelRenderer.showWire =true;
    motorControl.setup();

    stateController.setup(&ikController, &gaitController);
    balanceController.setup(true);



    isReady =true;
}

void Robot::update() {

    stateController.update();
    ikController.update();


    mat4 mat;
    mat = glm::toMat4(  imu.getQuat());
    mat = glm::translate(mat,vec3(  ikController.bodyX,ikController.bodyY,ikController.bodyZ)  );


    modelRenderer.model->setPosition(mat,ikController.angles);




    motorControl.setAngle(ikController.angles);
    modelRenderer.update();




}
void Robot::draw()
{
    motorControl.drawGui();
    GRAPH()->draw("motors");
    ikController.drawGui();
    modelRenderer.draw();
    stateController.draw();
    balanceController.drawGui();
}

