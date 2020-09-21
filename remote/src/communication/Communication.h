//
// Created by kris on 21.09.20.
//

#ifndef REMOTE_COMMUNICATION_H
#define REMOTE_COMMUNICATION_H
#include "cinder/app/App.h"
#include "OSCReceiver.h"
#include "OSCSender.h"
#include "../utils/Singleton.h"
class Communication
{
public:
    Communication();
    void setup();
    void update();
    void send( ci::osc::Message &message);
    OSCReceiver * receiver;
    OSCSender * sender;
};
typedef Singleton<Communication> CommunicationSingleton;

inline Communication *COM()
{
    return CommunicationSingleton::Instance();
}

#endif //REMOTE_COMMUNICATION_H
