#include "MotorControl.h"

#include "cinder/CinderImGui.h"

#include "../graph/GraphRenderer.h"

#include "../settings/SettingsHandler.h"


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
    if(true)
    {
        for (const auto &dev : Serial::getDevices())
        {

            string name = dev.getName();
            string t = name.substr(3, 3);
            if (t == "USB" || t == "Mot")
            {
                console() << "Device: " << name << endl;

            }
        }
    }



//fr
	MotorRef FRHip = Motor::create();
	FRHip->setup(SETTINGS()->getMotor("FRHip"));
	motors.push_back(FRHip);
    FRHip->motorGraph.gVisible =true;

    MotorRef FRKnee = Motor::create();
    FRKnee->setup(SETTINGS()->getMotor("FRKnee"));
    motors.push_back(FRKnee);
    FRKnee->motorGraph.gVisible =true;

    MotorRef FRAnkle = Motor::create();
    FRAnkle->setup(SETTINGS()->getMotor("FRAnkle"));
    motors.push_back(FRAnkle);
    FRAnkle->motorGraph.gVisible =true;
    //fl
    MotorRef FLHip = Motor::create();
    FLHip->setup(SETTINGS()->getMotor("FLHip"));
    motors.push_back(FLHip);

    MotorRef FLKnee = Motor::create();
    FLKnee->setup(SETTINGS()->getMotor("FLKnee"));
    motors.push_back(FLKnee);

    MotorRef FLAnkle = Motor::create();
    FLAnkle->setup(SETTINGS()->getMotor("FLAnkle"));
    motors.push_back(FLAnkle);

    //br
    MotorRef BRHip = Motor::create();
    BRHip->setup(SETTINGS()->getMotor("BRHip"));
    motors.push_back(BRHip);

    MotorRef BRKnee = Motor::create();
    BRKnee->setup(SETTINGS()->getMotor("BRKnee"));
    motors.push_back(BRKnee);

    MotorRef BRAnkle= Motor::create();
    BRAnkle->setup(SETTINGS()->getMotor("BRAnkle"));
    motors.push_back(BRAnkle);

    //bl
    MotorRef BLHip = Motor::create();
    BLHip->setup(SETTINGS()->getMotor("BLHip"));
    motors.push_back(BLHip);

    MotorRef BLKnee = Motor::create();
    BLKnee->setup(SETTINGS()->getMotor("BLKnee"));
    motors.push_back(BLKnee);

    MotorRef BLAnkle = Motor::create();
    BLAnkle->setup(SETTINGS()->getMotor("BLAnkle"));
    motors.push_back(BLAnkle);
}
void MotorControl::setAngle(std::vector<float>angles)
{
    if(!enableInput)return;
    if(motors.size()==angles.size())
    {
        for(int i=0;i<angles.size();i++)
        {
            motors[i]->setMotorAngle(angles[i]);
        }
    }
}
void MotorControl::drawGui()
{
    ImGui::Begin( "motors" );
    ImGui::Checkbox("enable input",&enableInput);
    if (ImGui::SliderFloat("all_MaxMotorSpeed", &motorSpeed, 0.f, 200000.f))
    {
        for(auto m:motors)
        {
            m->setMotorMaxSpeed(motorSpeed);
        }
    }
    if (ImGui::SliderFloat("all_motorKp", &kp, 0.f, 2000.f))
    {
        for(auto m:motors)
        {
            m->setMotorKp(kp);
        }

    }
    if (ImGui::SliderFloat("all_motorIntP", &motorIntP, 10.f, 255.f))
    {
        for(auto m:motors)
        {
            m->setMotorIntKpi(motorIntP,motorIntI);
        }

    }
    if (ImGui::SliderFloat("all_motorIntI", &motorIntI, 10.f, 255.f))
    {
        for(auto m:motors)
        {
            m->setMotorIntKpi(motorIntP,motorIntI);
        }

    }





	for (auto m : motors)
	{
		m->drawGui();
	}
    ImGui::End();


}

