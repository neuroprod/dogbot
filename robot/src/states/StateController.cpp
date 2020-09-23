//
// Created by kris on 19.08.20.
//

#include "StateController.h"
#include "StateEnum.h"
#include "cinder/CinderImGui.h"
#include "imgui/imgui_internal.h"

void StateController::setup(IKController *ikController, GaitController *gaitController)
{

    sitState = std::make_shared<StartState>();
   // states.push_back(sitState);

    standupState = std::make_shared<StandupState>();
    standupState->ikController = ikController;
    states.push_back(standupState);

    stepState = std::make_shared<StepState>();
    stepState->ikController = ikController;
    stepState->gaitController = gaitController;
    states.push_back(stepState);

    laydownState = std::make_shared<LaydownState>();
    laydownState->ikController = ikController;
    states.push_back(laydownState);


    currentState = sitState;


    currentState->start();

}

void StateController::update()
{
    currentState->update();


}

void StateController::setCommand(int type, int com)
{

    ci::app::console() << "command " << type << " " << com << std::endl;

}

void StateController::setNewState(std::shared_ptr<BaseState> state)
{

    currentState = state;


    currentState->start();

}

void StateController::reset()
{
    currentState = sitState;
    state = sitState->state;
    currentState->start();

}


void StateController::draw()
{
    ImGui::Begin("State");

    std::string n = "current state: " + currentState->getName();
    ImGui::Text("%s", n.c_str());
    if (currentState->isDone())
    {
        ImGui::TextColored(ImVec4(0, 1, 0, 1), "DONE");
    } else
    {
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "BUSY");
    }


    ImGui::Separator();
    for (int i = 0; i < states.size(); i++)
    {
        ImGui::PushID(i);
        if (ImGui::Button(states[i]->getName().c_str(), ImVec2(150.f, 0.0f)))
        {
            setNewState(states[i]);
        }
        if (states[i]->hasGui())
        {
            ImGui::SameLine();
            ImGui::Checkbox("show gui", &states[i]->showGui);
            if (states[i]->showGui)
            {

                ImGui::Indent(20);
                states[i]->drawGui();
                ImGui::Indent(-20);
                ImGui::Separator();
            }
        }
        ImGui::PopID();
    }
    /*bool disabled =true;
    if(state == STATE::NONE)
    {
        disabled =false;
    }
    if (disabled)
    {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }
    if(ImGui::Button("rise")){
        currentState =&riseState;
        state = riseState.state;
        currentState->start();

    }
    if(ImGui::Button("step")){
        currentState =&stepState;
        state = stepState.state;
        currentState->start();

    }
    if (disabled)
    {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }*/

    ImGui::End();

}