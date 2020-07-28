#include "MotorControl.h"

#include "cinder/CinderImGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;
//115200
void MotorControl::setup() 
{

    for( const auto &dev : Serial::getDevices() )
        console() << "Device: " << dev.getName() << endl;

	MotorRef FRHip = Motor::create();
	FRHip->setup(1, "FRHip","ttyUSB0");
	motors.push_back(FRHip);	
}

void MotorControl::drawGui()
{
    ImGui::Begin( "motors" );

	for (auto m : motors)
	{
		m->drawGui();
	}
    ImGui::End();
}

