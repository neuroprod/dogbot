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
    bool enableInput =true;
    float motorSpeed = 150000;
    float kp = 580;
	
};