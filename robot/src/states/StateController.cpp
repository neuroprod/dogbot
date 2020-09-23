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
void StateController::setCommand(int type,int com)
{

    ci::app::console()<<"command " <<type<<" "<<com<<std::endl;

}
void StateController::reset()
{
    currentState =&noneState;
    state = noneState.state;
    currentState->start();

}
void StateController::setNextState()
{




    switch ( state)
    {
        case STATE::RISE:
        {
            currentState =&noneState;
            state = noneState.state;
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
    ImGui::Text( "%s", n.c_str());


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