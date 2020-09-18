//
// Created by kris on 15.09.20.
//

#ifndef BOT_OSCSENDER_H
#define BOT_OSCSENDER_H
#include "cinder/osc/Osc.h"

using Sender = ci::osc::SenderUdp;
class OSCSender
{
public:
    OSCSender(uint16_t localPort, std::string destinationHost,uint16_t destinationPort): mSender( localPort, destinationHost, destinationPort ), mIsConnected( false ){}
    void setup();
    void send(ci::osc::Message &msg);
    void onSendError( asio::error_code error );
    Sender	mSender;
    bool	mIsConnected;
};


#endif //BOT_OSCSENDER_H
