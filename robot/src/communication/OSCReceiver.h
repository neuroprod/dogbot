//
// Created by kris on 15.09.20.
//

#ifndef REMOTE_OSCRECEIVER_H
#define REMOTE_OSCRECEIVER_H
#include "cinder/osc/Osc.h"

using Receiver = ci::osc::ReceiverUdp;
using protocol = asio::ip::udp;


class OSCReceiver
{
public:
    OSCReceiver(int port): mIoService( new asio::io_service ), mWork( new asio::io_service::work( *mIoService ) ),
    mReceiver( port, protocol::v4(), *mIoService ){};
    void setup();
    std::atomic<bool> hasNewCommand =false;
    std::atomic<bool> hasNewJoystick=false;

    std::shared_ptr<asio::io_service>		mIoService;
    std::shared_ptr<asio::io_service::work>	mWork;
    std::thread								mThread;
    std::mutex mMutex;


    Receiver mReceiver;
    std::map<uint64_t, protocol::endpoint> mConnections;
};


#endif //REMOTE_OSCRECEIVER_H
