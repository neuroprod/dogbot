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

    try
    {

        mSerial = Serial::create(Serial::Device("ttyACM0"), 115200);
    }
    catch (SerialExc &exc)
    {
        console() << "coult not initialize the serial device" << std::endl;

    }
    if (mSerial)
    {
        thread = std::thread(&RSerial::worker, this);
        isConnected = true;
    }

}

void RSerial::worker()
{
    while (true)
    {
        if (mSerial)
        {
            mSerial->writeByte(' ');
            std::string mLastString = mSerial->readStringUntil('\n', 80);
            if (mLastString.length() > 1)
            {
                std::vector<std::string> strings = ci::split(mLastString, ' ');
                if (strings.size() == 5)
                {


                    float i5 = std::stof(strings[4]);
                    mBattery = i5 / 1024.f;



                    float i1 = std::stof(strings[0]);//left hor
                    float i2 = std::stof(strings[1]);//left vert
                    float i3 = std::stof(strings[2]);//right vert
                    float i4 = std::stof(strings[3]);//right hor

                    joystick.setRaw(i1,i2,i4,i3);
                    /*
                    bool rDown = false;
                    if (i2 > 900)rDown = true;

                    bool lDown = false;
                    if (i3 > 900)lDown = true;

                    float xl = clampJoystick(i1 - 515.f)*-1;
                    float yl = clampJoystick((i2 - 512.f) * -1.f);


                    float xr = clampJoystick(i4 - 505.f)*-1;
                    float yr = clampJoystick((i3 - 515.f) * -1.f);


                    std::lock_guard<std::mutex> lock(dataMutex);


                    joystick.mRightJoystick.x = xr;
                    joystick.mRightJoystick.y = yr;
                    joystick.mLeftJoystick.x = xl;
                    joystick.mLeftJoystick.y = yl;
                    joystick.mLeftJoystickDown = lDown;
                    joystick.mRightJoystickDown = rDown;*/


                }
            }
        }
    }
}

float RSerial::clampJoystick(float in)
{
    if (in > 0)
    {

        in -= 20;
        if (in < 0)in = 0;
    }

    if (in < 0)
    {

        in += 20;
        if (in > 0)in = 0;
    }

    in /= 230.f;
    if (in > 1)in = 1;
    else if (in < -1)in = -1;

    return in;
}

Joystick RSerial::getJoystick()
{
    std::lock_guard<std::mutex> lock(dataMutex);
    return joystick;

}

float RSerial::getBatteryStatus()
{
    std::lock_guard<std::mutex> lock(dataMutex);
    return mBattery;
}