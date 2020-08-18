//
// Created by kris on 22.07.20.
//

#ifndef BOT_ROBOTMAIN_H
#define BOT_ROBOTMAIN_H
#include "cinder/app/App.h"
#include "motor/MotorControl.h"
#include "settings/SettingsHandler.h"
#include "modelrenderer/ModelRenderer.h"
#include "ik/IKControle.h"
class RobotMain
{
public:
    RobotMain(){};
    void setup();
    void update();
    void draw();

    Sint windowSizeX=SETTINGS()->getInt("RobotDebugSettings","windowSizeX",1920);
    Sint windowSizeY=SETTINGS()->getInt("RobotDebugSettings","windowSizeY",1080);

    IKControle ikControle;
    ModelRenderer modelRenderer;
    MotorControl motorControl;
};


#endif //BOT_ROBOTMAIN_H
