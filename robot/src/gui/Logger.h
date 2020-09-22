//
// Created by kris on 22.09.20.
//

#ifndef BOT_LOGGER_H
#define BOT_LOGGER_H
#include "cinder/app/App.h"
#include "cinder/CinderImGui.h"
class Logger
{
public:
    Logger(){};
    void log(std::string entry);
    void logError(std::string entry);
    void draw();
    ImVector<int>       LineOffsets;

    ImGuiTextBuffer     Buf;
};


#endif //BOT_LOGGER_H
