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
    float bodyX =SETTINGS()->getFloat("RobotSettings","bodyX",0)->value();
    float bodyXStart =SETTINGS()->getFloat("RobotSettings","bodyXStart",-27)->value();
    float bodyYStart =SETTINGS()->getFloat("RobotSettings","bodyYStart",80)->value();

    float bodyLength =SETTINGS()->getFloat("RobotSettings","bodyLength",352.f)->value();
    float bodyWidth =SETTINGS()->getFloat("RobotSettings","bodyWidth",120.f)->value();

    float hipOffsetX =SETTINGS()->getFloat("RobotSettings","hipOffsetX ",60.f)->value();
    float hipOffsetZ = SETTINGS()->getFloat("RobotSettings","hipOffsetZ",74.f)->value();
    float upperLegLength = SETTINGS()->getFloat("RobotSettings","upperLegLength",210.f)->value();
    float underLegLength =SETTINGS()->getFloat("RobotSettings","underLegLength",250.f)->value();

    float footRadius =SETTINGS()->getFloat("RobotSettings","footRadius",20.f)->value();

    float bodyMass =SETTINGS()->getFloat("RobotSettings","bodyMass",4.f)->value();
    ci::vec3 bodyCOM = SETTINGS()->getVec3("RobotSettings","bodyCOM",ci::vec3(0,0,0))->mValue;

    float hipMass = SETTINGS()->getFloat("RobotSettings","hipMass",1.f)->value();
    ci::vec3 hipCOM =SETTINGS()->getVec3("RobotSettings","hipCOM",ci::vec3( 50, 0, 0))->mValue;

    float kneeMass = SETTINGS()->getFloat("RobotSettings","kneeMass",1.f)->value();
    ci::vec3 kneeCOM =SETTINGS()->getVec3("RobotSettings","kneeCOM",ci::vec3(0, -120, 0))->mValue;


    float ankleMass = SETTINGS()->getFloat("RobotSettings","ankleMass",1.f)->value();;
    ci::vec3 ankleCOM =SETTINGS()->getVec3("RobotSettings","ankleCOM",ci::vec3(0, -120, 0))->mValue;


    float toeMass = SETTINGS()->getFloat("RobotSettings","toeMass",0.5f)->value();
    ci::vec3 toeCOM =SETTINGS()->getVec3("RobotSettings","toeCOM",ci::vec3(0, -0, 0))->mValue;




};
typedef Singleton<RobotSettings > RobotSettingsSingleton;

inline RobotSettings * BOTSETTINGS() {
    return  RobotSettingsSingleton::Instance();
}
#endif //BOT_ROBOTSETTINGS_H
