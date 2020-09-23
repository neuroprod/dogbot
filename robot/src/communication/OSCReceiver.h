//
// Created by kris on 15.09.20.
//

#ifndef REMOTE_OSCRECEIVER_H
#define REMOTE_OSCRECEIVER_H
#include "cinder/osc/Osc.h"
#include "../input/Joystick.h"
using Receiver = ci::osc::ReceiverUdp;
using protocol = asio::ip::udp;


class OSCReceiver
{
public:
    OSCReceiver(int port): mIoService( new asio::io_service ), mWork( new asio::io_service::work( *mIoService ) ),
    mReceiver( port, protocol::v4(), *mIoService ){};
    void setup();

    void updateJoystick(JoystickRef joystick );
    ci::ivec2 getCommand( );
    std::atomic<bool> hasNewCommand =false;
    std::atomic<bool> hasNewJoystick=false;

    std::shared_ptr<asio::io_service>		mIoService;
    std::shared_ptr<asio::io_service::work>	mWork;

    std::mutex mCommandMutex;
    std::mutex mJoystickMutex;

    Receiver mReceiver;
    std::thread   mThread;

    float JLeftX =0;
    float JLeftY =0;
    bool JLeftDown=0;
    float JRightX =0;
    float  JRightY =0;
    bool JRightDown =0;
bool btnDown =false;
    int commandType;
    int command;
};


#endif //REMOTE_OSCRECEIVER_H
