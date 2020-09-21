


#include "cinder/CinderImGui.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "settings/SettingsHandler.h"
#include "serialInput/RSerial.h"
#include "communication/Communication.h"

using namespace ci;
using namespace ci::app;
using namespace std;
class RemoteApp : public App
{
public:
    void setup() override;

    void update() override;

    void draw() override;


    bool isFS =false;
    RSerial serial;
};

void RemoteApp::setup()
{
    setFrameRate(60);
    setWindowSize(800, 480);
    ImGui::Initialize();
    serial.setup();
    COM()->setup();

}


void RemoteApp::update()
{
    COM()->update();
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

    SETTINGS()->load({"AppSettings","ComSettings"});
}
)