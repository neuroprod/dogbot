//
// Created by kris on 22.07.20.
//
#include "cinder/gl/gl.h"
#include "RobotMain.h"
#include "cinder/Serial.h"
#include <signal.h>
#include <JetsonGPIO.h>
#include "cinder/CinderImGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;

void RobotMain::setup() {
    ImGui::Initialize();
    motorControl.setup();
   // GPIO::setmode(GPIO::BOARD);
    //GPIO::setup(12, GPIO::OUT, GPIO::HIGH);
}

void RobotMain::update() {
    motorControl.drawGui();
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
    gl::clear();

}