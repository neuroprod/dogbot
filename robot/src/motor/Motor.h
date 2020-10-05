#pragma once
#include "cinder/app/App.h"
#include "cinder/Serial.h"
#include "../settings/SettingMotor.h"
#include "../graph/GraphableArray.h"
class Motor;
typedef std::shared_ptr<Motor> MotorRef;
enum class MOTOR_STATE { NONE, POSITION,KILL,SET_ZERO,SET_PID,READ_PID };
class Motor {



	float motorAngle = 0;
	float motorSpeed = 150000;
    float motorSpeedUI = motorSpeed;
    float kp = 650;
    float kpUI= kp ;

   int motorPosP=100;
    int motorPosI=100;
    int motorSpeedP=50;
    int motorSpeedI=40;
    int motorTorqueP=50;
    int motorTorqueI=50;




    void updatePID();
    void updatePosition();
    void shutDown();
    void setZero();
    void readPID();
	void setPositionData( int64_t angle, int32_t speed);
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
    std::mutex stateMutex;
	std::vector< uint8_t> data;
	ci::SerialRef my_serial;
	bool connectionFailed = false;

	float angleUI = 0;


	float prevAngleTarget = 0;

	ci::vec3 motorData;

    Smotor mSettings;



    double prevTime =0;
    //MOTOR_STATE currentStateTarget = MOTOR_STATE::SET_ZERO;
    MOTOR_STATE currentStateTarget = MOTOR_STATE::POSITION;
  // MOTOR_STATE currentStateTarget = MOTOR_STATE::READ_PID;

public:
	Motor() {};
    GraphableArray motorGraph;
	static MotorRef create();
	void setup(Smotor settings);
	void drawGui();
    void setState( MOTOR_STATE state);
	void setMotorAngle(float angle);
    void setMotorKp(float target);
    void setMotorIntPID(int pp,int pi,int sp,int si,int tp,int ti);
	void setMotorMaxSpeed(float speed);
	ci::vec3 getData();
	
	///////////////////////
	


};