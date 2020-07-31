//
// Created by kris on 22.07.20.
//

#ifndef BOT_SETTINGFLOAT_H
#define BOT_SETTINGFLOAT_H

class SettingFloat : public SettingBase
{
    float mValue;
public:
    SettingFloat()
    {}

    SettingFloat(std::string file, std::string key, float defaultValue = 0.0f)
    {
        mFile = file;
        mKey = key;
        mValue = defaultValue;
        mType = "float";
    }

    void setFromJson(ci::JsonTree &json) override
    {
        mValue = json.getValue<float>();
    }


    ci::JsonTree toJson() override
    {
        ci::JsonTree json = ci::JsonTree::makeObject();
        json.addChild(ci::JsonTree("key", mKey));
        json.addChild(ci::JsonTree("value", mValue));
        json.addChild(ci::JsonTree("type", mType));
        return json;
    }

    float &value()
    {
        return mValue;
    }


};

typedef std::shared_ptr <SettingFloat> Sfloat;
#endif //BOT_SETTINGFLOAT_H
