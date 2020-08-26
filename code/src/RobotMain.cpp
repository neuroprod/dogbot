//
// Created by kris on 22.07.20.
//
#include "cinder/gl/gl.h"
#include "RobotMain.h"
#include "cinder/Serial.h"
#include <signal.h>
#include <JetsonGPIO.h>
#include "cinder/CinderImGui.h"
#include "graph/GraphRenderer.h"
using namespace ci;
using namespace ci::app;
using namespace std;

void RobotMain::setup() {



    ikControle.setup();
    modelRenderer.setup();
    modelRenderer.showMesh =false;
    modelRenderer.showWire =true;
    motorControl.setup();
   // GPIO::setmode(GPIO::BOARD);
    //GPIO::setup(12, GPIO::OUT, GPIO::HIGH);
}

void RobotMain::update() {
    ikControle.update();
    modelRenderer.model->setPosition(ikControle.bodyMatrix,ikControle.angles);
    modelRenderer.update();


  /*int a = ci::app::getElapsedSeconds() ;
  if(a%2==0){
    GPIO::output(12, GPIO::HIGH);
  }else
      {
          GPIO::output(12, GPIO::LOW);

      }*/
}
void RobotMain::draw()
{
    motorControl.drawGui();
    GRAPH()->draw();
    ikControle.drawGui();
    modelRenderer.draw();

}

