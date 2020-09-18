


#include "cinder/CinderImGui.h"
#include "gui/GuiSetup.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "settings/SettingsHandler.h"
#include "RobotSettings.h"
#include "cinder/gl/gl.h"


#include "Simulation.h"

#include "Robot.h"
#include "communication/OSCSender.h"


using namespace ci;
using namespace ci::app;

class BotApp : public App
{
public:
    void setup() override;

    void update() override;

    void draw() override;

    void imGuiUpdate();

    void setupImGui();

    RobotSettings settings; //auto init of settings
    GuiSetup guiSetup;

    Simulation simulation;
    Robot robot;

    Sbool isSimulation = SETTINGS()->getBool("AppSettings", "isSimulation", true);
    Sint windowSizeX = SETTINGS()->getInt("AppSettings", "windowSizeX", 1920);
    Sint windowSizeY = SETTINGS()->getInt("AppSettings", "windowSizeY", 1080);

    OSCSender sender = OSCSender (10000,"127.0.0.1",10001);

};

void BotApp::setup()
{
sender.setup();
    setFrameRate(120);
    gl::enableVerticalSync(false);

    setWindowSize(windowSizeX->value(), windowSizeY->value());
    guiSetup.setup();

    if (isSimulation->value())
    {
        simulation.setup();
    } else
    {
        robot.setup();
    }


}


void BotApp::update()
{
    ci::osc::Message msg( "/mousemove/1" );
    msg.append( 101 );
    msg.append( 100 );
    sender.send(msg);

    guiSetup.update();

    if (isSimulation->value())
    {
        if (!simulation.isReady)simulation.setup();
        simulation.update();
    } else
    {
        if (!robot.isReady)robot.setup();
        robot.update();
    }


}

void BotApp::draw()
{
    if (isSimulation->value())
    {
        simulation.draw();
    } else
    {
        robot.draw();
    }

}




CINDER_APP(BotApp, RendererGl, [](App::Settings *settings)
{
    SETTINGS()->load({"AppSettings", "RobotSettings", "MotorSettings"});
    settings->setWindowPos(0,0);
}
)