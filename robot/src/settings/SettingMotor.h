//
// Created by kris on 31.07.20.
//

#ifndef BOT_SETTINGMOTOR_H
#define BOT_SETTINGMOTOR_H
#include "SettingBase.h"

class SettingMotor: public SettingBase
        {

public:
    SettingMotor()
    {}

    SettingMotor( std::string key)
    {
        mFile = "MotorSettings";
        mType = "motor";

        mKey = key;


    }

    void setFromJson(ci::JsonTree &json) override
    {
        //mValue = json.getValue<int>();
        mID =json.getChild("id").getValue<int>();
        mPort =json.getChild("port").getValue<std::string>();

        mMin =json.getChild("min").getValue<float>();
        mMax =json.getChild("max").getValue<float>();

        mOffsetInput =json.getChild("offsetInput").getValue<float>();
        reverse =json.getChild("reverse").getValue<bool>();


    }


    ci::JsonTree toJson() override
    {
        ci::JsonTree json = ci::JsonTree::makeObject();
        json.addChild(ci::JsonTree("key", mKey));
        json.addChild(ci::JsonTree("type", mType));

        ci::JsonTree jsonVal = ci::JsonTree::makeObject("value");

        jsonVal.addChild(ci::JsonTree("id",mID));
        jsonVal.addChild(ci::JsonTree("port",mPort));
        jsonVal.addChild(ci::JsonTree("reverse",reverse));
        jsonVal.addChild(ci::JsonTree("offsetInput",mOffsetInput));
        jsonVal.addChild(ci::JsonTree("min",mMin));
        jsonVal.addChild(ci::JsonTree("max",mMax));

        json.addChild(jsonVal);

        return json;
    }

    int mID =0;
    float mOffsetInput=0.f ;
    float mMin=-30.f ;
    float mMax=30.f ;
  bool reverse =false;

    std::string mPort="ttyMotorName" ;


};

typedef std::shared_ptr <SettingMotor> Smotor;

#endif //BOT_SETTINGMOTOR_H
