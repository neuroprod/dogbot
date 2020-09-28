//
// Created by kris on 22.07.20.
//

#include "Robot.h"

#include "cinder/CinderImGui.h"
#include "graph/GraphRenderer.h"
#include "Status.h"
#include "communication/Communication.h"
using namespace ci;
using namespace ci::app;
using namespace std;

void Robot::setup() {

    joystick =std::make_shared<Joystick>();
    gaitController.setup( );
    imu.start();
    ikController.setup();
    modelRenderer.setup();
    modelRenderer.showMesh =false;
    modelRenderer.showWire =true;
    motorControl.setup();

    stateController.setup(&ikController, &gaitController,&balanceController);
    balanceController.setup(true);



    isReady =true;
}

void Robot::update() {

    vec3  euler=imu.getEuler();
    balanceController.update(euler.x,euler.y);

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
    stateController.update();
    ikController.update();


    mat4 mat;
 //   mat = glm::toMat4(  imu.getQuat());
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
    gaitController.drawGui();
    modelRenderer.draw();
    stateController.draw();
    balanceController.drawGui();
    STATUS()->drawGui();
}

