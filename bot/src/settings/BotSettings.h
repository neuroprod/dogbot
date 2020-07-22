//
// Created by kris on 29.06.20.
//

#ifndef BOT_BOTSETTINGS_H
#define BOT_BOTSETTINGS_H

#include "cinder/Json.h"
#include "cinder/app/App.h"
#include "Singleton.h"
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



class SettingFloat: public SettingBase
{
   float mValue;
public:
    SettingFloat()
    {}

    SettingFloat(std::string file, std::string key, float defaultValue=0.0f)
    {
        mFile = file;
        mKey = key;
        mValue = defaultValue;
        mType ="float";
    }

    void setFromJson(ci::JsonTree &json) override
    {
        mValue = json.getValue<float>();
    }


    ci::JsonTree toJson() override
    {
        ci::JsonTree json =  ci::JsonTree::makeObject();
        json.addChild(ci::JsonTree("key", mKey));
        json.addChild(ci::JsonTree("value", mValue));
        json.addChild(ci::JsonTree("type",  mType));
        return json;
    }

   float &value()
    {
        return mValue;
    }


};
typedef std::shared_ptr<SettingFloat> Sfloat;


class BotSettings
{

    std::vector<std::shared_ptr<SettingBase>> settings;
public:
    BotSettings()
    {};

    Sfloat getFloat(std::string file, std::string key, float defaultValue)
    {

        for (auto s:settings)
        {

            if (s->mFile == file && s->mKey == key)
            {
                return std::dynamic_pointer_cast<SettingFloat>(s);
            }
        }
        auto s = std::make_shared<SettingFloat>(file, key, defaultValue);
        settings.push_back(s);
        ci::app::console() << "init" << std::endl;
        return s;
    }



    void save()
    {
        auto sortRule = [](std::shared_ptr<SettingBase> s1, std::shared_ptr<SettingBase> s2) -> bool
        {
            return s1->mFile < s2->mFile;
        };

        std::sort(settings.begin(), settings.end(), sortRule);

        std::string currentFile = "";
        ci::JsonTree settingsJson = ci::JsonTree::makeArray();
        for (auto s : settings)
        {
            if (s->mFile != currentFile)
            {
                if (settingsJson.getNumChildren())
                {

                    saveSettingsFile(settingsJson, currentFile);
                }
                settingsJson = ci::JsonTree::makeArray();
                currentFile = s->mFile;
            }
            settingsJson.pushBack(s->toJson());

        }
        if (settingsJson.getNumChildren())
        {
            saveSettingsFile(settingsJson, currentFile);
        }
    }

    void saveSettingsFile(ci::JsonTree const &settingsJson, std::string const &filename)
    {
        std::string settingPath = ci::app::getAssetPath("").string() + filename + ".json";
        std::ofstream settingFile(settingPath, std::ios::out);
        settingFile << settingsJson.serialize();
        settingFile.close();
        ci::app::console() << "save " << settingsJson.getNumChildren() << " settings to:" << filename << std::endl;


    }

    void load(std::vector<std::string> files)
    {
        for (auto filename:files)
        {
            std::string settingPath = ci::app::getAssetPath("").string() + filename + ".json";
            if (!ci::fs::exists(settingPath))
            {
                CI_LOG_E("CAN'T FIND SETTING FILE " + settingPath);
                continue;
            }

            std::ifstream input(settingPath.c_str());
            if (!input.is_open())
            {
                CI_LOG_E("CAN'T OPEN SETTING FILE " + settingPath);
                continue;
            } else
            {


                std::string file_contents{std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};

                ci::JsonTree storedSettingsJson = ci::JsonTree(file_contents);
                input.close();
                int numC = storedSettingsJson.getNumChildren();
                CI_LOG_I("found " << numC  << " settings");
               for(size_t i=0;i<numC ;i++)
                {
                   ci::JsonTree s = storedSettingsJson.getChild(i);
                   std::string type =s.getChild("type").getValue<std::string>();
                   std::string key =s.getChild("key").getValue<std::string>();
                   ci::JsonTree val =s.getChild("value");

                  if(type =="float"){

                      auto s = std::make_shared<SettingFloat>(filename, key);
                      s->setFromJson(val);
                      settings.push_back(s);
                  }
                }


            }

        }

    }


};

typedef Singleton<BotSettings> BotSettingsSingleton;

inline BotSettings *BS()
{
    return BotSettingsSingleton::Instance();
}

#endif //BOT_BOTSETTINGS_H
