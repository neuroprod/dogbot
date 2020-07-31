//
// Created by kris on 29.06.20.
//

#ifndef BOT_BOTSETTINGS_H
#define BOT_BOTSETTINGS_H

#include "cinder/Json.h"
#include "cinder/app/App.h"
#include "../utils/Singleton.h"
#include "cinder/Log.h"
#include "../settings/SettingBase.h"
#include "../settings/SettingFloat.h"
#include "../settings/SettingInt.h"
#include "../settings/SettingMotor.h"
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
        return s;
    }
    Sint getInt(std::string file, std::string key, int defaultValue)
    {
        for (auto s:settings)
        {
            if (s->mFile == file && s->mKey == key)
            {
                return std::dynamic_pointer_cast<SettingInt>(s);
            }
        }
        auto s = std::make_shared<SettingInt>(file, key, defaultValue);
        settings.push_back(s);
        return s;
    }
    Smotor getMotor( std::string key)
    {
        for (auto s:settings)
        {
            if (s->mFile == "MotorSettings" && s->mKey == key)
            {
                return std::dynamic_pointer_cast<SettingMotor>(s);
            }
        }
        auto s = std::make_shared<SettingMotor>( key);
        settings.push_back(s);
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
        std::string settingPath = ci::app::getAssetPath("settings/").string() + filename + ".json";
        std::ofstream settingFile(settingPath, std::ios::out);
        settingFile << settingsJson.serialize();
        settingFile.close();
        ci::app::console() << "save " << settingsJson.getNumChildren() << " settings to:" << filename << std::endl;


    }

    void load(std::vector<std::string> files)
    {
        for (auto filename:files)
        {
            std::string settingPath = ci::app::getAssetPath("settings/").string() + filename + ".json";
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
                CI_LOG_I("found " << numC << " settings");
                for (size_t i = 0; i < numC; i++)
                {
                    ci::JsonTree s = storedSettingsJson.getChild(i);
                    std::string type = s.getChild("type").getValue<std::string>();
                    std::string key = s.getChild("key").getValue<std::string>();
                    ci::JsonTree val = s.getChild("value");

                    if (type == "float")
                    {

                        auto s = std::make_shared<SettingFloat>(filename, key);
                        s->setFromJson(val);
                        settings.push_back(s);
                    }
                    if (type == "int")
                    {

                        auto s = std::make_shared<SettingInt>(filename, key);
                        s->setFromJson(val);
                        settings.push_back(s);
                    }
                    if (type == "motor")
                    {

                        auto s = std::make_shared<SettingMotor>( key);
                        s->setFromJson(val);
                        settings.push_back(s);
                    }
                }

            }

        }

    }


};

typedef Singleton<BotSettings> BotSettingsSingleton;

inline BotSettings *SETTINGS()
{
    return BotSettingsSingleton::Instance();
}

#endif //BOT_BOTSETTINGS_H
