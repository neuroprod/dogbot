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



    ikControle.setup();
    modelRenderer.setup();
    modelRenderer.showMesh =false;
    modelRenderer.showWire =true;
    motorControl.setup();

    imu.start();

   // GPIO::setmode(GPIO::BOARD);
    //GPIO::setup(12, GPIO::OUT, GPIO::HIGH);

    isReady =true;
}

void Robot::update() {
    ikControle.update();


    mat4 mat;
    mat = glm::toMat4(imu.getQuat());
    modelRenderer.model->setPosition(mat,ikControle.angles);
    
    modelRenderer.update();



  /*int a = ci::app::getElapsedSeconds() ;
  if(a%2==0){
    GPIO::output(12, GPIO::HIGH);
  }else
      {
          GPIO::output(12, GPIO::LOW);

      }*/
}
void Robot::draw()
{
    motorControl.drawGui();
    GRAPH()->draw();
    ikControle.drawGui();
    modelRenderer.draw();
    imu.drawGui();
}

