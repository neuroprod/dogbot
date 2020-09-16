//
// Created by kris on 15.09.20.
//

#include "RSerial.h"
#include "cinder/Utilities.h"
void RSerial::setup()
{
    for( const auto &dev : Serial::getDevices() )
        console() << "Device: " << dev.getName() << endl;

    try {

        mSerial = Serial::create(Serial::Device("ttyACM0"), 115200 );
    }
    catch( SerialExc &exc ) {
        console()<< "coult not initialize the serial device"<<endl;

    }
    if(mSerial)
    {
        thread = std::thread(&RSerial::worker, this);

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
                    float i1 = std::stof(strings[0]);
                    console() << i1 << endl;
                }
            }

        }
    }

}

ci::vec2 RSerial::getRightJoystick()
{
    std::lock_guard<std::mutex> lock( dataMutex );
    return mRightJoyStick;


}
ci::vec2 RSerial::getLeftJoystick()
{
    std::lock_guard<std::mutex> lock( dataMutex );
    return mLeftJoyStick;
}
float RSerial::getBatteryStatus()
{
    std::lock_guard<std::mutex> lock( dataMutex );
    return mBattery;
}