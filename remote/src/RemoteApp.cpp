


#include "cinder/CinderImGui.h"

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

#include "cinder/gl/gl.h"
#include "ADS1115.h"

using namespace ci;
using namespace ci::app;

class RemoteApp : public App
{
public:
    void setup() override;

    void update() override;

    void draw() override;

    ADS1115 joysticks;
};

void RemoteApp::setup()
{
    setFrameRate(60);
    gl::enableVerticalSync(false);

    setWindowSize(500, 300);

    joysticks.setup();

}


void RemoteApp::update()
{
    joysticks.update();

}

void RemoteApp::draw()
{


}


CINDER_APP(RemoteApp, RendererGl, [](App::Settings *settings)
{


}
)