//
// Created by kris on 17.08.20.
//

#ifndef BOT_ROBOTSETTINGS_H
#define BOT_ROBOTSETTINGS_H
#include "settings/SettingsHandler.h"

class RobotSettings
{
public:
    RobotSettings(){};
    float bodyY =SETTINGS()->getFloat("RobotSettings","bodyY",300)->value();
    float bodyXStart =SETTINGS()->getFloat("RobotSettings","bodyXStart",-27)->value();
    float bodyYStart =SETTINGS()->getFloat("RobotSettings","bodyYStart",80)->value();
    float bodyLength =SETTINGS()->getFloat("RobotSettings","bodyLength",352.f)->value();
    float bodyWidth =SETTINGS()->getFloat("RobotSettings","bodyWidth",120.f)->value();

    float hipOffsetX =SETTINGS()->getFloat("RobotSettings","hipOffsetX ",60.f)->value();
    float hipOffsetZ = SETTINGS()->getFloat("RobotSettings","hipOffsetZ",74.f)->value();
    float upperLegLength = SETTINGS()->getFloat("RobotSettings","upperLegLength",210.f)->value();
    float underLegLength =SETTINGS()->getFloat("RobotSettings","underLegLength",250.f)->value();

    float footRadius =SETTINGS()->getFloat("RobotSettings","footRadius",20.f)->value();

};
typedef Singleton<RobotSettings > RobotSettingsSingleton;

inline RobotSettings * BOTSETTINGS() {
    return  RobotSettingsSingleton::Instance();
}
#endif //BOT_ROBOTSETTINGS_H
