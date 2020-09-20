//
// Created by kris on 22.07.20.
//
#include "cinder/gl/gl.h"
#include "Robot.h"
#include "cinder/Serial.h"
#include <signal.h>
#include <JetsonGPIO.h>
#include "cinder/CinderImGui.h"
#include "graph/GraphRenderer.h"
using namespace ci;
using namespace ci::app;
using namespace std;

void Robot::setup() {

/*    GPIO::setmode(GPIO::BOARD);

    GPIO::setup(15, GPIO::OUT, GPIO::HIGH);
   // GPIO::setup(13, GPIO::OUT, GPIO::HIGH);
*/

    ikControle.setup();
    modelRenderer.setup();
    modelRenderer.showMesh =false;
    modelRenderer.showWire =true;
    motorControl.setup();

  //  imu.start();



    isReady =true;
}

void Robot::update() {
    ikControle.update();


    mat4 mat;
    mat = glm::toMat4(imu.getQuat());
    modelRenderer.model->setPosition(mat,ikControle.angles);
    motorControl.setAngle(ikControle.angles);
    modelRenderer.update();




}
void Robot::draw()
{
    motorControl.drawGui();
    GRAPH()->draw("motors");
    ikControle.drawGui();
    modelRenderer.draw();
    imu.drawGui();
}

