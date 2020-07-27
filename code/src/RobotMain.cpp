//
// Created by kris on 22.07.20.
//

#include "RobotMain.h"
#include "cinder/Serial.h"
#include <signal.h>
#include <JetsonGPIO.h>


using namespace ci;
using namespace ci::app;
using namespace std;

void RobotMain::setup() {
    for( const auto &dev : Serial::getDevices() ) {
        console() << "Device: " << dev.getName() << endl;
    }

    GPIO::setmode(GPIO::BOARD);
    GPIO::setup(12, GPIO::OUT, GPIO::HIGH);
}

void RobotMain::update() {

  int a = ci::app::getElapsedSeconds() ;
  if(a%2==0){
    GPIO::output(12, GPIO::HIGH);
  }else
      {
          GPIO::output(12, GPIO::LOW);

      }
}
void RobotMain::draw()
{


}