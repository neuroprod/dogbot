


#include "cinder/CinderImGui.h"

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

#include "cinder/gl/gl.h"

#include "communication/OSCReceiver.h"
#include "cinder/CinderImGui.h"
#include "settings/SettingsHandler.h"
#include "serialInput/RSerial.h"
using namespace ci;
using namespace ci::app;
using namespace std;
class RemoteApp : public App
{
public:
    void setup() override;

    void update() override;

    void draw() override;
    RSerial serial;
    OSCReceiver receiver;

    bool isFS =false;
};

void RemoteApp::setup()
{

    ImGui::Initialize();

    setFrameRate(60);


    setWindowSize(800, 480);

    serial.setup();
    receiver.setup();
}


void RemoteApp::update()
{

    ImGui::Begin("Settings");
    if(ImGui::Checkbox("fullscreen", &isFS)){setFullScreen(isFS);}
    ImGui::End();

}

void RemoteApp::draw()
{
    gl::clear();

}


CINDER_APP(RemoteApp, RendererGl, [](App::Settings *settings)
{

    SETTINGS()->load({"AppSettings"});
}
)