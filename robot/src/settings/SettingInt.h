//
// Created by kris on 22.07.20.
//

#ifndef BOT_SETTINGINT_H
#define BOT_SETTINGINT_H

class SettingInt: public SettingBase
{
    int mValue;
public:
    SettingInt()
    {}

    SettingInt(std::string file, std::string key, int defaultValue = 0)
    {
        mFile = file;
        mKey = key;
        mValue = defaultValue;
        mType = "int";
    }

    void setFromJson(ci::JsonTree &json) override
    {
        mValue = json.getValue<int>();
    }


    ci::JsonTree toJson() override
    {
        ci::JsonTree json = ci::JsonTree::makeObject();
        json.addChild(ci::JsonTree("key", mKey));
        json.addChild(ci::JsonTree("value", mValue));
        json.addChild(ci::JsonTree("type", mType));
        return json;
    }

    int &value()
    {
        return mValue;
    }
    void setValue( int val)
    {
        mValue =val;
    }

};

typedef std::shared_ptr <SettingInt> Sint;
#endif //BOT_SETTINGINT_H
