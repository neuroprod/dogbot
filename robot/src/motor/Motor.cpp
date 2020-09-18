#include "Motor.h"
#include "cinder/CinderImGui.h"
#include "../utils/Unions.h"
#include <sstream>

#include <unistd.h>       // Used for UART
#include <sys/fcntl.h>    // Used for UART
#include <termios.h>      // Used for UART
#include "../graph/GraphRenderer.h"
using namespace ci;
using namespace ci::app;
using namespace std;

MotorRef Motor::create()
{
	return make_shared<Motor>();
}

void Motor::setup(Smotor settings)
{
    mSettings =settings;
    id =   mSettings->mID  ;
	name = mSettings->mKey;
    port ="ttyUSB0";//  mSettings->mPort;
    angleTarget = mSettings->mStartValue;
    motorAngle = angleTarget+mSettings->mOffset;



    motorGraph.prepGraph(name,3,{0.5f,0.4f,100.f/65000.f},{Color(1,0,0),Color(0,1,0),Color(0,0,1)},{"Torque","Speed","Encoder"} );

    GRAPH()->reg(&motorGraph);

    unsigned long baud = 115200;


    try {
        Serial::Device dev = Serial::findDeviceByNameContains( port );
        my_serial = Serial::create(dev, baud);



           my_serial->flush();
            motorThread = std::thread(&Motor::loop, this);

    }
    catch (...)
    {
        connectionFailed = true;
    }
    if (connectionFailed) {
        console() << "Failed to connect to " << (int)id << " " << name << " " << port << endl;
    }
    else
    {
        console() << "Connected to " << (int)id << " " << name << " " << port << endl;

    }


}
void Motor::loop()
{

    bool nComplete = true;
    std::vector<uint8_t> buffer;

    std::this_thread::sleep_for (std::chrono::milliseconds(1000));


    while (nComplete)
    {
        inMutex.lock();
        float maxSpeed = motorSpeed;
        float  angleTarget = motorAngle;
        float  kpR = kp;
        inMutex.unlock();

        //speed = dps*100

        uint32_t speedR= maxSpeed;
        int64_t  angleR = (angleTarget ) * 100.f * 6.f;

        float angleChange = abs(prevAngleTarget - angleTarget);
        uint32_t speed = angleChange *60 * kpR;
        if (speed < speedR && speed !=0)speedR = speed;
       // console() << angleChange <<" "<< speed << " " << speedR << " "<< my_serial->getNumBytesAvailable() << endl;
        prevAngleTarget = angleTarget;


        setPosition(id, angleR, speedR);

        my_serial->writeBytes(&data[0], data.size());


       /* std::this_thread::sleep_for (std::chrono::milliseconds(16));
         console()<<my_serial->getNumBytesAvailable()<<endl;
        my_serial->flush();*/

      while ((my_serial->getNumBytesAvailable() != 13)) {
          std::this_thread::sleep_for (std::chrono::milliseconds(1));
      }

        buffer.clear();
        buffer.resize(13);
        my_serial->readBytes(&buffer[0], 13);

        Union16 Utorque;
        Utorque.b[0] = buffer[6];
        Utorque.b[1] = buffer[7];

        Union16 Uspeed;
        Uspeed.b[0] = buffer[8];
        Uspeed.b[1] = buffer[9];

        UnionU16 Uencoder;
        Uencoder.b[0] = buffer[10];
        Uencoder.b[1] = buffer[11];

        outMutex.lock();
        motorData.x = Utorque.r;
        motorData.y = Uspeed.r;
        motorData.z = Uencoder.r;
        outMutex.unlock();

        if(test) {

            shutDown( id);
        }
      //  console() << (float)Utorque.r / 2048.f * 33.f << " " << (float)Uspeed.r << " " << (float)Uencoder.r << endl;
      /*  std::this_thread::sleep_for (std::chrono::seconds(5));
       *
        shutDown( id);
        my_serial->writeBytes(&data[0], data.size());*/
    }
}


void Motor::drawGui()
{
    ImGui::PushID(name.c_str());
    ImGui::SetNextTreeNodeOpen(true);
    ci::vec3 mData = getData();

    if (ImGui::CollapsingHeader(name.c_str()))
    {
       float angle = (float)mData.z*360.f /65536.f/6.f;
        ImGui::Text("tes %f",angle );
        if (ImGui::SliderFloat("motorAngle", &angleTarget, mSettings->mMin, mSettings->mMax)) { setMotorAngle(angleTarget); }
        if (ImGui::SliderFloat("motorSpeed", &speedTarget, 0.f, 200000.f)) { setMotorMaxSpeed(speedTarget); }
        if (ImGui::SliderFloat("motorKp", &kpTarget, 0.f, 2000.f)) { inMutex.lock(); kp = kpTarget;     inMutex.unlock();}
        if (ImGui::SliderFloat("motorOffset", &mSettings->mOffset, 0, 60)) { setMotorAngle(angleTarget); }
        if (ImGui::InputFloat("inputOffset", &mSettings->mOffsetInput)) {  }
    }
    if(motorGraph.gVisible)
    {

        motorGraph.addData({ mData.x,mData.y,mData.z  });

    }
    ImGui::PopID();


}

void Motor::setMotorAngle(float target)
{
    inMutex.lock();
    motorAngle = target+mSettings->mOffset;

   
    inMutex.unlock();
}
void Motor::setMotorMaxSpeed(float target)
{
    inMutex.lock();
    motorSpeed =target;

   
    inMutex.unlock();
}

vec3 Motor::getData()
{
    vec3 data;
    outMutex.lock();
    data = motorData;
    outMutex.unlock();
    return data;
}


//////////////////////////////////////////////////////////
void Motor::setPosition(uint8_t id, int64_t angleControl, int32_t maxSpeed)
{
    angleControl = angleControl;
    makeHeader(0xA4, 1, 0x0C);
    data.push_back(*(uint8_t*)(&angleControl));
    data.push_back(*((uint8_t*)(&angleControl) + 1));
    data.push_back(*((uint8_t*)(&angleControl) + 2));
    data.push_back(*((uint8_t*)(&angleControl) + 3));
    data.push_back(*((uint8_t*)(&angleControl) + 4));
    data.push_back(*((uint8_t*)(&angleControl) + 5));
    data.push_back(*((uint8_t*)(&angleControl) + 6));
    data.push_back(*((uint8_t*)(&angleControl) + 7));
    data.push_back(*(uint8_t*)(&maxSpeed));
    data.push_back(*((uint8_t*)(&maxSpeed) + 1));
    data.push_back(*((uint8_t*)(&maxSpeed) + 2));
    data.push_back(*((uint8_t*)(&maxSpeed) + 3));

    addCheckSum();

}
void Motor::readAngle(uint8_t id)
{

    makeHeader(0x92, 1, 0x00);

    addCheckSum();

}
void Motor::shutDown(uint8_t id)
{

    makeHeader(0x80, 1, 0x00);

    addCheckSum();

}
void Motor::makeHeader(uint8_t command, uint8_t id, uint8_t dataLength)
{
    data.clear();
    data.push_back(0x3E);
    data.push_back(command);
    data.push_back(id);
    data.push_back(dataLength);

    uint8_t ssum = 0x3E + command + id + dataLength;
    data.push_back(ssum);
}
void Motor::addCheckSum()
{
    uint8_t ssum = data[5];
    for (int i = 6; i < data.size(); i++)
    {
        ssum += data[i];
    }
    data.push_back(ssum);
}

void Motor::logData()
{
    for (int i = 0; i < data.size(); i++)
    {
        console() << toHexString(data[i]) << " ";
    }
    console() << endl;
}
std::string Motor::toHexString(uint8_t b)
{
    std::stringstream str;
    str << std::hex << static_cast<int>((b));
    std::string result(str.str());
    if (result.size() == 1) result = "0" + result;
    std::for_each(result.begin(), result.end(), [](char& c) {
        c = ::toupper(c);
        });
    return result;

}