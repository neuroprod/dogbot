//
// Created by kris on 15.09.20.
//

#include "OSCReceiver.h"

using namespace ci;
using namespace ci::app;
using namespace std;

void OSCReceiver::setup()
{
    mReceiver.setListener("/command",
                          [&](const osc::Message &msg)
                          {
                              mCommandMutex.lock();
                              commandType = msg[0].int32();
                             command = msg[1].int32();
                              mCommandMutex.unlock();
                              hasNewCommand = true;



                          });

    mReceiver.setListener("/joystick",
                          [&](const osc::Message &msg)
                          {
                              mJoystickMutex.lock();

                              JLeftX = msg[0].flt();
                              JLeftY= msg[1].flt();
                              JLeftDown = msg[2].boolean();
                              JRightX = msg[3].flt();
                              JRightY = msg[4].flt();
                              JRightDown = msg[5].boolean();
                              hasNewJoystick= true;
                              mJoystickMutex.unlock();
                           
                          });

    try
    {
        mReceiver.bind();
    }
    catch (const osc::Exception &ex)
    {
        console() << "Error binding: " << ex.what() << " val: " << ex.value() << endl;
        return;
    }


    mReceiver.listen(
            [](asio::error_code error, protocol::endpoint endpoint) -> bool
            {
                if (error)
                {
                    console() << "Error Listening: " << error.message() << " val: "
                              << error.value() << " endpoint: " << endpoint << endl;
                    return false;
                } else
                    return true;
            });


    // Now that everything is setup, run the io_service on the other thread.
    mThread = std::thread(std::bind(
            [](std::shared_ptr<asio::io_service> &service)
            {
                service->run();
            }, mIoService));

}
void OSCReceiver::updateJoystick(JoystickRef joystick )
{
    mJoystickMutex.lock();
    joystick->mLeftJoystick.x = JLeftX;
    joystick->mLeftJoystick.y = JLeftY;
    joystick->mLeftJoystickDown = JLeftDown;
    joystick->mRightJoystick.x = JRightX;
    joystick->mRightJoystick.y = JRightY;
    joystick->mRightJoystickDown = JRightDown;
    hasNewJoystick = false;
    mJoystickMutex.unlock();
}
ivec2 OSCReceiver::getCommand( )
{
    mCommandMutex.lock();
    ivec2 a;
    a.x = commandType;
    a.y =command;
    mCommandMutex.unlock();
    hasNewCommand = false;
    return a;
}