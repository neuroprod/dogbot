
#define SIMULATION

#include "cinder/CinderImGui.h"

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "settings/SettingsHandler.h"
#include "RobotSettings.h"

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


    void draw() override;
    void imGuiUpdate();
    void setupImGui();
    RobotSettings settings; //auto init of settings

#ifdef SIMULATION
SimulationMain simulation;
#else
RobotMain robot;
#endif


};

void BotApp::setup()
{
    setFrameRate(120);
    gl::enableVerticalSync(false);
    setupImGui();






#ifdef SIMULATION
    simulation.setup();
#else
robot.setup();
#endif

    SETTINGS()->save();
}




void BotApp::update()
{
    imGuiUpdate();

    //ImGui::ShowDemoWindow();



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
void  BotApp::setupImGui()
{

    ImGui::Initialize();
    ImGuiIO& io = ImGui::GetIO();


    io.Fonts->AddFontFromFileTTF(getAssetPath("fonts/Ubuntu-R.ttf").c_str(), 16.0f);

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
    colors[ImGuiCol_ChildBg]                = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.20f, 0.21f, 0.22f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.40f, 0.40f, 0.40f, 0.40f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.18f, 0.18f, 0.18f, 0.67f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.44f, 0.44f, 0.44f, 0.40f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.46f, 0.47f, 0.48f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.70f, 0.70f, 0.70f, 0.31f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.70f, 0.70f, 0.70f, 0.80f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.48f, 0.50f, 0.52f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.72f, 0.72f, 0.72f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_TabActive]        = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.91f, 0.91f, 0.91f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.81f, 0.81f, 0.81f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.46f, 0.46f, 0.46f, 0.95f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.73f, 0.60f, 0.15f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.87f, 0.87f, 0.87f, 0.35f);
    colors[ImGuiCol_ModalWindowDarkening]   = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);

}
void  BotApp::imGuiUpdate()
{
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    bool open =true;
    ImGui::Begin("DockSpace Demo", &open, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {

            ImGui::EndMenu();
        }
      /* if (ImGui::BeginMenu("Examples"))
        {
            ImGui::MenuItem("Main menu bar", NULL);

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools"))
        {
            ImGui::MenuItem("Metrics", NULL);
            ImGui::MenuItem("Style Editor", NULL);
            ImGui::MenuItem("About Dear ImGui", NULL);
            ImGui::EndMenu();
        }*/
        ImGui::EndMenuBar();
    }
    ImGui::End();


    ImGui::Begin("performance");
    ImGui::Text("fps:%f",ImGui::GetIO().Framerate);
    ImGui::End();
}


CINDER_APP( BotApp, RendererGl, [] ( App::Settings *settings ) {
    SETTINGS()->load({"SimulationSettings","RobotSettings","RobotDebugSettings","MotorSettings"});

}
)