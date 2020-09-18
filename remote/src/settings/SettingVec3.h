//
// Created by kris on 30.08.20.
//

#ifndef BOT_SETTINGVEC3_H
#define BOT_SETTINGVEC3_H
#include "SettingBase.h"

class SettingVec3: public SettingBase
{

public:

    ci::vec3 mValue;


    SettingVec3()
    {}

    SettingVec3(std::string file, std::string key,  ci::vec3 defaultValue = ci::vec3(0))
    {
        mFile = file;
        mKey = key;
        mValue = defaultValue;
        mType = "vec3";
    }

    void setFromJson(ci::JsonTree &json) override
    {

        mValue.x =json.getChild("x").getValue<float>();
        mValue.y =json.getChild("y").getValue<float>();
        mValue.z =json.getChild("z").getValue<float>();

    }


    ci::JsonTree toJson() override
    {
        ci::JsonTree json = ci::JsonTree::makeObject();
        json.addChild(ci::JsonTree("key", mKey));
        json.addChild(ci::JsonTree("type", mType));

        ci::JsonTree jsonVal = ci::JsonTree::makeObject("value");

        jsonVal.addChild(ci::JsonTree("x",mValue.x));
        jsonVal.addChild(ci::JsonTree("y",mValue.y));
        jsonVal.addChild(ci::JsonTree("z",mValue.z));

        json.addChild(jsonVal);

        return json;
    }




};

typedef std::shared_ptr <SettingVec3> Svec3;
#endif //BOT_SETTINGVEC3_H
