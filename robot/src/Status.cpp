//
// Created by kris on 22.09.20.
//
#include "cinder/CinderImGui.h"
#include "Status.h"

using namespace std;

void Status::drawGui()
{
    ImGui::Begin("Status");
    logger.draw();

    ImGui::End();
}

void Status::log(string entry)
{
    std::lock_guard<std::mutex> lock(logMutex);
    logger.log(entry+"\n");

}

void Status::logError(string entry, bool isFatal)
{

    if (isFatal)mHasFatal = true;
    std::lock_guard<std::mutex> lock(logMutex);
    logger.logError(entry+"\n");
}

bool Status::isFatalError()
{
    return mHasFatal;

}
