//
// Created by kris on 19.08.20.
//

#include "StateController.h"
#include "StateEnum.h"
#include "cinder/CinderImGui.h"
#include "imgui/imgui_internal.h"
void StateController::setup(IKController * ikController, GaitController *gaitController ){

    riseState.ikController  = ikController;

    stepState.ikController  = ikController;
    stepState.gaitController  = gaitController;

    if(true) //if simulation
    {
        currentState = &riseState;
        state = riseState.state;
        currentState->start();
    }
    currentState =&noneState;
    state = noneState.state;

    currentState->start();

}
void StateController::update()
{
    currentState->update();
    if(currentState->isDone())
    {
        setNextState();

    }

}

void StateController::setNextState()
{

    if(autoNextState == false )
    {
        currentState =&noneState;
        state = noneState.state;
        return;
    }


    switch ( state)
    {
        case STATE::RISE:
        {
            currentState =&stepState;
            state = stepState.state;
            currentState->start();

            break;
        }
        case STATE::STEP:
        {
            //if(blabla):
           currentState->start();
            break;
        }

    }
}

void StateController::draw()
{
    ImGui::Begin("State");
    std::string n = "current state: "+currentState->getName();
    ImGui::Text( n.c_str());

    ImGui::Checkbox("auto next state",&autoNextState);
    ImGui::Separator();

    bool disabled =true;
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
    }

    ImGui::End();

}