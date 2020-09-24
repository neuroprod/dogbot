//
// Created by kris on 22.09.20.
//
#include "cinder/CinderImGui.h"
#include "Status.h"

using namespace std;

void Status::drawGui()
{
    ImGui::Begin("Status");
    ImGui::Text("fps:%f", ImGui::GetIO().Framerate);
    logger.draw();

    ImGui::End();
}

void Status::log(string entry)
{
    std::lock_guard<std::mutex> lock(logMutex);
    logger.log(entry+"\n");

}
void Status::logWarning(string entry)
{
    std::lock_guard<std::mutex> lock(logMutex);
    logger.logWarning(entry+"\n");

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
