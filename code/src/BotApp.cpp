#ifndef __arm__
//#define SIMULATION
#endif

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

#include "settings/BotSettings.h"

#ifdef SIMULATION
#include "SimulationMain.h"
#else
#include "RobotMain.h"
#endif

using namespace ci;
using namespace ci::app;

class BotApp : public App {
public:
    void setup() override;
    void update() override;
  /*  void resize() override;
    void mouseDown( MouseEvent event ) override;
    void mouseDrag( MouseEvent event ) override;*/
    void draw() override;


#ifdef SIMULATION
SimulationMain simulation;
#else
RobotMain robot;
#endif


};

void BotApp::setup()
{




#ifdef SIMULATION
    simulation.setup();
#else
robot.setup();
#endif

    SETTINGS()->save();
}
/*
void BotApp::resize() {

}
void BotApp::mouseDown( MouseEvent event )
{

}

void BotApp::mouseDrag( MouseEvent event ) {

}*/
void BotApp::update()
{
#ifdef SIMULATION
    simulation.update();
#else
robot.update();

#endif

}
void BotApp::draw()
{
#ifdef SIMULATION
    simulation.draw();
#else
    robot.draw();
#endif

}

CINDER_APP( BotApp, RendererGl, [] ( App::Settings *settings ) {
    SETTINGS()->load({"SimulationSettings"});

}
)