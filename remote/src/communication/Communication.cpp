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
    int receivePort =10002;
    int receivePortDest =10001;
    int sendPort =10000;
    std::string destinationHost = "192.168.1.124";
    receiver =new OSCReceiver(receivePort );
    receiver->setup();
    sender =new OSCSender(sendPort,destinationHost,receivePortDest );
    sender->setup();
}
void Communication::send(ci::osc::Message &message)
{
    sender->send(message);

}
void Communication::update()
{


}
