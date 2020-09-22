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
#include "walking/GaitController.h"
#include "balance/BalanceController.h"
#include "states/StateController.h"

class Robot
{
public:
    Robot(){};
    void setup();
    void update();
    void draw();

    IMU imu;
    IKController ikController;
    ModelRenderer modelRenderer;
    MotorControl motorControl;
    StateController stateController;
    GaitController gaitController;
    BalanceController balanceController;

    bool isReady =false;
};


#endif //BOT_ROBOT_H
