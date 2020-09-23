

#include "gui/GuiSetup.h"
#include "cinder/CinderImGui.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "settings/SettingsHandler.h"
#include "serialInput/RSerial.h"
#include "serialInput/Joystick.h"
#include "communication/Communication.h"

using namespace ci;
using namespace ci::app;
using namespace std;
class RemoteApp : public App
{
public:
    void setup() override;

    void update() override;
    void sendCommand(int type,int command ) ;
    void draw() override;
    void drawMain();
    void drawJoystick();

    GuiSetup guiSetup;


    RSerial serial;
    Joystick joystick;


    int  currentGui =0;
};

void RemoteApp::setup()
{
    std::vector<std::string> args = getCommandLineArgs();
    for(auto s: args)
    {
        console()<<s<<std::endl;

    }
    bool useDevIP =false;
    if (std::find(args.begin(), args.end(), "devIP") !=args.end())
    {
        useDevIP =true;
    }
    COM()->setup(useDevIP);

    setFrameRate(60);
    setWindowSize(800, 480);
    guiSetup.setup();
    serial.setup();


}
void RemoteApp::sendCommand(int type,int command)
{

    ci::osc::Message msg("/command");
    msg.append( type);
    msg.append(command );
    COM()->send(msg);

}
void RemoteApp::update()
{
    joystick =serial.getJoystick();
    ci::osc::Message msg =joystick.getMessage();
    COM()->send(msg);
    COM()->update();
    if( currentGui ==0)
    {
        drawMain();
    }else
        {

        drawJoystick();
        }

}
void  RemoteApp::drawMain()
{
    ImGuiWindowFlags window_flags = 0;

    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoNav;
    window_flags |= ImGuiWindowFlags_NoBackground;

    bool open = true;


    float firstColumnWidth =600;
    float secondColumnWith =800-firstColumnWidth-1;
    float firstColumnWidthP =firstColumnWidth-15;
    float secondColumnWidthP =secondColumnWith-15;
    ImGui::Begin("cont",&open,window_flags);

    ImGui::Columns(2);
    static unsigned short initial_column_spacing = 0;

    if (initial_column_spacing < 2)
    {
        ImGui::SetColumnWidth(0, firstColumnWidth);
        initial_column_spacing++;
    }

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8,0,0,1));
    if(ImGui::Button("abort",ImVec2(firstColumnWidthP , 60))){
        sendCommand(0,0);

    }

    ImGui::PopStyleColor(1);
    ImGui::Dummy(ImVec2(0.0f, 50.0f));
    if(ImGui::Button("stand",ImVec2(firstColumnWidthP , 30))){
        sendCommand(1,1);

    }
    if(ImGui::Button("laydown",ImVec2(firstColumnWidthP , 30))){
        sendCommand(1,2);

    }
    if(ImGui::Button("walk",ImVec2(firstColumnWidthP , 30))){
        sendCommand(1,3);

    }
    ImGui::Dummy(ImVec2(0.0f, 50.0f));
    if(ImGui::Button("test1",ImVec2(firstColumnWidthP , 30))){
        sendCommand(2,1);

    }
    if(ImGui::Button("test2",ImVec2(firstColumnWidthP , 30))){
        sendCommand(2,2);

    }
    if(ImGui::Button("test3",ImVec2(firstColumnWidthP , 30))){
        sendCommand(2,3);

    }
    if(ImGui::Button("test4",ImVec2(firstColumnWidthP , 30))){
        sendCommand(2,4);

    }
    ImGui::Dummy(ImVec2(0.0f, 50.0f));
    ImGui::NextColumn();
    if(ImGui::Button("toggle fullscreen",ImVec2(secondColumnWidthP , 25))){
        setFullScreen(!isFullScreen());
        if(isFullScreen()){
            hideCursor();
        }else
        {showCursor();}
    }
    ImGui::Dummy(ImVec2(0.0f, 2.0f));
    if(ImGui::Button("joystick settings",ImVec2(secondColumnWidthP , 25))){
       currentGui=1;
    }
    ImGui::Dummy(ImVec2(0.0f, 2.0f));
    if(ImGui::Button("save settings",ImVec2(secondColumnWidthP , 25))){
        SETTINGS()->save();
    }
    ImGui::Columns(1);
    ImGui::End();

}
void  RemoteApp::drawJoystick()
{
    ImGuiWindowFlags window_flags = 0;

    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoNav;
    window_flags |= ImGuiWindowFlags_NoBackground;

    bool open = true;


    ImGui::Begin("cont",&open,window_flags);
    if(ImGui::Button("back",ImVec2(0 , 25))){
        currentGui=0;
    }
    joystick.drawDebugGui();
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