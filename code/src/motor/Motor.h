#pragma once
#include "cinder/app/App.h"
#include "cinder/Serial.h"
#include "../settings/SettingMotor.h"
#include "../graph/GraphableArray.h"
class Motor;
typedef std::shared_ptr<Motor> MotorRef;

class Motor {
    bool test =true;
	float motorAngle = 0;
	float motorSpeed = 1600;
	void setPosition(uint8_t id, int64_t angle, int32_t speed);
    void readAngle(uint8_t id);
    void shutDown(uint8_t id);
	void makeHeader(uint8_t command, uint8_t id, uint8_t dataLength);
	void addCheckSum();
	void logData();
	std::string toHexString(uint8_t b);
	void loop();

	uint8_t id;
	std::string name;
	std::string port;

	std::thread motorThread;
	std::mutex inMutex;
	std::mutex outMutex;
	std::vector< uint8_t> data;
	ci::SerialRef my_serial;
	bool connectionFailed = false;

	float angleTarget = 0;
	float speedTarget = motorSpeed;
	float prevAngleTarget = 0;
	float kpTarget = 580;
	float kp = kpTarget;
	ci::vec3 motorData;

    Smotor mSettings;

    GraphableArray motorGraph;
public:
	Motor() {};

	static MotorRef create();
	void setup(Smotor settings);
	void drawGui();

	void setMotorAngle(float angle);

	void setMotorMaxSpeed(float speed);
	ci::vec3 getData();
	
	///////////////////////
	


};