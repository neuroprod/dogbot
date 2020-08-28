//
// Created by kris on 28.08.20.
//

#ifndef BOT_SETTINGBOOLEAN_H
#define BOT_SETTINGBOOLEAN_H
class SettingBoolean: public SettingBase
{
   bool mValue;
public:
    SettingBoolean()
    {}

    SettingBoolean(std::string file, std::string key, bool defaultValue = false)
    {
        mFile = file;
        mKey = key;
        mValue = defaultValue;
        mType = "bool";
    }

    void setFromJson(ci::JsonTree &json) override
    {
        mValue = json.getValue<bool>();
    }


    ci::JsonTree toJson() override
    {
        ci::JsonTree json = ci::JsonTree::makeObject();
        json.addChild(ci::JsonTree("key", mKey));
        json.addChild(ci::JsonTree("value", mValue));
        json.addChild(ci::JsonTree("type", mType));
        return json;
    }

    bool &value()
    {
        return mValue;
    }


};

typedef std::shared_ptr <SettingBoolean> Sbool;
#endif //BOT_SETTINGBOOLEAN_H
