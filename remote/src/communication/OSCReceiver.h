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
    OSCReceiver():mReceiver(10001){};
    void setup();
    Receiver mReceiver;
    std::map<uint64_t, protocol::endpoint> mConnections;
};


#endif //REMOTE_OSCRECEIVER_H
