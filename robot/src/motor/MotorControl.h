#pragma once

#include "cinder/app/App.h"

#include "Motor.h"

class MotorControl
{

public:
	MotorControl() {}
	void setup();
	void drawGui();
	std::vector<MotorRef> motors;
    void setAngle(std::vector<float>angles);
    void setPID();
    bool enableInput =true;
    float motorSpeed = 150000;
    float kp = 650;
    int motorPosP=100;
    int motorPosI=100;
    int motorSpeedP=50;
    int motorSpeedI=40;
    int motorTorqueP=50;
    int motorTorqueI=50;
};