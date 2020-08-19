//
// Created by kris on 19.08.20.
//

#include "StateControle.h"
#include "StateEnum.h"
#include "cinder/CinderImGui.h"
#include "imgui/imgui_internal.h"
void StateControle::setup(IKControle * ikControle ){

    riseState.ikControle  = ikControle;





    currentState =&noneState;
    state = noneState.state;

    currentState->start();

}
void StateControle::update()
{
    currentState->update();
    if(currentState->isDone())
    {
        setNextState();

    }

}

void StateControle::setNextState()
{

    if(autoNextState == false )
    {
        currentState =&noneState;
        state = noneState.state;
        return;
    }


    switch ( state)
    {
        case STATE::NONE:
        {

        }
        break;
    }
}

void StateControle::draw()
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
    if (disabled)
    {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }

    ImGui::End();

}