//
// Created by kris on 21.09.20.
//

#include "Communication.h"
#include "../settings/SettingsHandler.h"
using namespace std;
using namespace ci;
using namespace ci::app;

Communication::Communication()
{

}

void Communication::setup(bool useDevIP)
{
    int receivePort =10001;
    int receivePortDest =10002;
    int sendPort =10000;
    std::string destinationHost =SETTINGS()->getString("AppSettings","RemoteIP","192.168.4.1")->value();
    if(useDevIP)
    {
        destinationHost = SETTINGS()->getString("AppSettings", "devRemoteIP", "192.168.1.80")->value();
    }

    receiver =new OSCReceiver(receivePort );
    receiver->setup();
    sender =new OSCSender(sendPort,destinationHost,receivePortDest );
    sender->setup();
}

void Communication::update()
{

}