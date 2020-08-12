#include "MotorControl.h"

#include "cinder/CinderImGui.h"
#include "../settings/BotSettings.h"

using namespace ci;
using namespace ci::app;
using namespace std;
//115200
void MotorControl::setup() 
{
	//udevadm info --name=/dev/ttyUSBx --attribute-walk
	///set device in: etc/udev/rules.d/99-usb-serial.rules
	// SUBSYSTEM=="tty", ATTRS{idVendor}=="1234", ATTRS{idProduct}=="5678", SYMLINK+="your_device_name"
	//reload: sudo udevadm trigger
    for( const auto &dev : Serial::getDevices() )
        console() << "Device: " << dev.getName() << endl;




	MotorRef FRHip = Motor::create();
	FRHip->setup(SETTINGS()->getMotor("FRHip"));
	motors.push_back(FRHip);

    MotorRef FLHip = Motor::create();
    FLHip->setup(SETTINGS()->getMotor("FLHip"));
    motors.push_back(FLHip);

    MotorRef BRHip = Motor::create();
    BRHip->setup(SETTINGS()->getMotor("BRHip"));
    motors.push_back(BRHip);

    MotorRef BLHip = Motor::create();
    BLHip->setup(SETTINGS()->getMotor("BLHip"));
    motors.push_back(BLHip);
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

