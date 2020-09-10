#pragma once
#include "cinder/app/App.h"
class PID 
{
public:
    PID() {};
    float calculate(float target,float current);

    void drawGui(std::string name);
    float  output =0;
    float dt = 1.0f/120.f;
	float max =150;
	float min = -30;
	float Kp =55;
	float Ki = 0.0;
	float Kd =0;
	float error = 0;;
	float pre_error = 0;
	float integral = 0;
	bool inv = false;
	std::vector<float> errors;
};