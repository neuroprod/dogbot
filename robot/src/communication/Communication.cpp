//
// Created by kris on 21.09.20.
//

#include "Communication.h"
using namespace std;
using namespace ci;
using namespace ci::app;

Communication::Communication()
{

}

void Communication::setup()
{
    int receivePort =10001;
    int receivePortDest =10002;
    int sendPort =10000;
    std::string destinationHost = "192.168.1.80";
    receiver =new OSCReceiver(receivePort );
    receiver->setup();
    sender =new OSCSender(sendPort,destinationHost,receivePortDest );
    sender->setup();
}

void Communication::update()
{

}