//
// Created by kris on 22.07.20.
//

#ifndef BOT_SETTINGBASE_H
#define BOT_SETTINGBASE_H

#include "cinder/Json.h"
#include "cinder/app/App.h"
#include "../utils/Singleton.h"
#include "cinder/Log.h"

class SettingBase
{
public:
    SettingBase()
    {};

    virtual ci::JsonTree toJson()
    { return ci::JsonTree("data", ""); };

    virtual void setFromJson(ci::JsonTree &json)
    {};


    std::string mKey;
    std::string mFile;
    std::string mType;
};


#endif //BOT_SETTINGBASE_H
