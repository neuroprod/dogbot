//
// Created by kris on 22.07.20.
//

#ifndef BOT_SIMULATIONMAIN_H
#define BOT_SIMULATIONMAIN_H

#include "cinder/app/App.h"
#include "settings/SettingsHandler.h"
#include "graph/GraphableArray.h"
#include "modelrenderer/ModelRenderer.h"
class SimulationMain
{
public:
    SimulationMain(){}
    void setup();
    void update();
    void draw();

    Sint windowSizeX=SETTINGS()->getInt("SimulationSettings","windowSizeX",2560);
    Sint windowSizeY=SETTINGS()->getInt("SimulationSettings","windowSizeY",1440);

    ModelRenderer modelRenderer;

    GraphableArray test;
    GraphableArray test2;
};


#endif //BOT_SIMULATIONMAIN_H
