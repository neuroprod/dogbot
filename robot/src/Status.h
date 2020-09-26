//
// Created by kris on 22.09.20.
//

#ifndef BOT_STATUS_H
#define BOT_STATUS_H
#include "cinder/app/App.h"
#include "utils/Singleton.h"
#include "gui/Logger.h"
#include "gui/SoundHandler.h"
class Status
{
public:
    Status(){}

    void log(std::string entry);
    void logError(std::string entry,bool fatal);
    void logWarning(std::string entry);
    std::mutex logMutex;
    Logger logger;
    bool isFatalError();
    std::atomic<bool> mHasFatal =false;
    SoundHandler soundHandler;

    void drawGui();

};

typedef Singleton<Status> StatusSingleton;

inline Status *STATUS()
{
    return StatusSingleton::Instance();
}


#endif //BOT_STATUS_H
