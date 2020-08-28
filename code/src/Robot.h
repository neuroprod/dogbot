//
// Created by kris on 22.07.20.
//

#ifndef BOT_ROBOT_H
#define BOT_ROBOT_H
#include "cinder/app/App.h"
#include "motor/MotorControl.h"
#include "settings/SettingsHandler.h"
#include "modelrenderer/ModelRenderer.h"
#include "ik/IKController.h"
#include "balance/IMU.h"

class Robot
{
public:
    Robot(){};
    void setup();
    void update();
    void draw();


    IKController ikControle;
    ModelRenderer modelRenderer;
    MotorControl motorControl;
    IMU imu;
    bool isReady =false;
};


#endif //BOT_ROBOT_H
