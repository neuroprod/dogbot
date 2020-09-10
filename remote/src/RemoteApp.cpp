


#include "cinder/CinderImGui.h"

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

#include "cinder/gl/gl.h"


using namespace ci;
using namespace ci::app;

class RemoteApp : public App
{
public:
    void setup() override;

    void update() override;

    void draw() override;


};

void RemoteApp::setup()
{
    setFrameRate(60);
    gl::enableVerticalSync(false);

    setWindowSize(300, 500);


}


void RemoteApp::update()
{


}

void RemoteApp::draw()
{


}


CINDER_APP(RemoteApp, RendererGl, [](App::Settings *settings)
{


}
)