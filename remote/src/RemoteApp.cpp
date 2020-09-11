


#include "cinder/CinderImGui.h"

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

#include "cinder/gl/gl.h"
#ifdef CINDER_GL_ES_3_RPI
#include "ADS1115.h"
#endif  
using namespace ci;
using namespace ci::app;

class RemoteApp : public App
{
public:
    void setup() override;

    void update() override;

    void draw() override;
#ifdef CINDER_GL_ES_3_RPI
    ADS1115 joysticks;
#endif
};

void RemoteApp::setup()
{
    setFrameRate(60);
    gl::enableVerticalSync(false);

    setWindowSize(500, 300);
#ifdef CINDER_GL_ES_3_RPI
    joysticks.setup();
 #endif   
}


void RemoteApp::update()
{
    #ifdef CINDER_GL_ES_3_RPI
    joysticks.update();
#endif CINDER_GL_ES_3_RPI
}

void RemoteApp::draw()
{


}


CINDER_APP(RemoteApp, RendererGl, [](App::Settings *settings)
{


}
)