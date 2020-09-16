//
// Created by kris on 15.09.20.
//

#include "RSerial.h"
#include "cinder/Utilities.h"
using namespace ci;
using namespace ci::app;
void RSerial::setup()
{
    //for( const auto &dev : Serial::getDevices() )
     //   console() << "Device: " << dev.getName() << std::endl;

    try {

        mSerial = Serial::create(Serial::Device("ttyACM0"), 115200 );
    }
    catch( SerialExc &exc ) {
        console()<< "coult not initialize the serial device"<<std::endl;

    }
    if(mSerial)
    {
        thread = std::thread(&RSerial::worker, this);
        isConnected =true;
    }

}
void RSerial::worker()
{
    while(true)
    {
        if (mSerial)
        {
            std::string mLastString = mSerial->readStringUntil('\n', 80);
            if (mLastString.length() > 1)
            {
                std::vector<std::string> strings=    ci::split(mLastString,' ');
                if(strings.size()==5)
                {
                    float i1 = std::stof(strings[0]);//right hor
                    float i2 = std::stof(strings[1]);//right vert
                    float i3 = std::stof(strings[2]);//left vert
                    float i4 = std::stof(strings[3]);//left hor
                    float i5 = std::stof(strings[4]);

                    bool rDown =false;    
                    if(i2 >900)rDown =true;

                    bool lDown =false;    
                    if(i3 >900)lDown =true;

                    float xr =clampJoystick(i1-515.f);
                    float yr =clampJoystick((i2-512.f) *-1.f);


                    float xl =clampJoystick(i4-505.f);
                    float yl =clampJoystick((i3-515.f) *-1.f);


                    std::lock_guard<std::mutex> lock( dataMutex );

                    mBattery =i5/1024.f;
                    mRightJoystick.x=xr;
                    mRightJoystick.y=yr;
                    mLeftJoystick.x=xl;
                    mLeftJoystick.y=yl;
                    mLeftJoystickDown =lDown;
                    mRightJoystickDown=rDown;


                }
            }
        }
    }
}
float RSerial::clampJoystick(float in)
{
        if(in>0){

            in-=20;
            if(in<0)in=0;
        }
        
        if(in<0){

            in+=20;
            if(in>0)in=0;
        }
        
        in/=230.f;
        if(in>1)in=1;
        else if(in<-1)in=-1;

        return in;
}
bool RSerial::getRightJoystickDown()
{
    std::lock_guard<std::mutex> lock( dataMutex );
    return mRightJoystickDown;


}
bool RSerial::getLeftJoystickDown()
{
    std::lock_guard<std::mutex> lock( dataMutex );
    return mLeftJoystickDown;
}
ci::vec2 RSerial::getRightJoystick()
{
    std::lock_guard<std::mutex> lock( dataMutex );
    return mRightJoystick;


}
ci::vec2 RSerial::getLeftJoystick()
{
    std::lock_guard<std::mutex> lock( dataMutex );
    return mLeftJoystick;
}
float RSerial::getBatteryStatus()
{
    std::lock_guard<std::mutex> lock( dataMutex );
    return mBattery;
}