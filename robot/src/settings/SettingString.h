//
// Created by kris on 21.09.20.
//

#ifndef BOT_SETTINGSTRING_H
#define BOT_SETTINGSTRING_H


class SettingString: public SettingBase
{
    std::string mValue;
public:
    SettingString()
    {}

    SettingString(std::string file, std::string key, std::string defaultValue ="")
    {
        mFile = file;
        mKey = key;
        mValue = defaultValue;
        mType = "string";
    }

    void setFromJson(ci::JsonTree &json) override
    {
        mValue = json.getValue<std::string>();
    }


    ci::JsonTree toJson() override
    {
        ci::JsonTree json = ci::JsonTree::makeObject();
        json.addChild(ci::JsonTree("key", mKey));
        json.addChild(ci::JsonTree("value", mValue));
        json.addChild(ci::JsonTree("type", mType));
        return json;
    }

    std::string &value()
    {
        return mValue;
    }
    void setValue( int val)
    {
        mValue =val;
    }

};

typedef std::shared_ptr <SettingString> Sstring;
#endif //BOT_SETTINGSTRING_H
