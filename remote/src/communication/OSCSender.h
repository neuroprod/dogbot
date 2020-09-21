//
// Created by kris on 15.09.20.
//

#ifndef BOT_OSCSENDER_H
#define BOT_OSCSENDER_H

#include "cinder/osc/Osc.h"


using Sender = ci::osc::SenderUdp;
using protocol = asio::ip::udp;


class OSCSender
{
public:
    OSCSender(uint16_t localPort, std::string destinationHost,uint16_t destinationPort): mIoService( new asio::io_service ), mWork( new asio::io_service::work( *mIoService ) ),
    mSender( 10000, destinationHost, destinationPort, protocol::v4(), *mIoService ),
    mIsConnected( false ){};
    void setup();
    void send(ci::osc::Message &msg);
    void onSendError( asio::error_code error );

    std::shared_ptr<asio::io_service>		mIoService;
    std::shared_ptr<asio::io_service::work>	mWork;
    std::thread								mThread;

    Sender	mSender;
    std::atomic_bool	mIsConnected;
};


#endif //BOT_OSCSENDER_H
