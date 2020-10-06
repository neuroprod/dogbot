//
// Created by kris on 19.08.20.
//

#include "StateController.h"
#include "StateEnum.h"
#include "cinder/CinderImGui.h"
#include "imgui/imgui_internal.h"
#include "../Status.h"
#include "../graph/GraphRenderer.h"
using namespace std;
using namespace ci;
using namespace ci::app;

void StateController::setup(IKController *ikController, GaitController *gaitController,BalanceController *balanceController)
{

    sitState = std::make_shared<StartState>();
    // states.push_back(sitState);

    standupState = std::make_shared<StandUpState>();
    standupState->ikController = ikController;
    standupState->balanceController= balanceController;
    states.push_back(standupState);

    stepState = std::make_shared<StepState>();
    stepState->ikController = ikController;
    stepState->gaitController = gaitController;
    stepState->balanceController= balanceController;
    states.push_back(stepState);

    laydownState = std::make_shared<LayDownState>();
    laydownState->ikController = ikController;
    states.push_back(laydownState);

////tests
    test2LegsUpState = std::make_shared<Test2LegsUpState>();
    test2LegsUpState->ikController = ikController;
    test2LegsUpState->balanceController= balanceController;
    states.push_back(test2LegsUpState);

    testAllLegsDownState = std::make_shared<TestAllLegsDownState>();
    testAllLegsDownState->ikController = ikController;
    testAllLegsDownState->balanceController= balanceController;
    states.push_back(testAllLegsDownState);

    currentState = sitState;


    currentState->start();

}

void StateController::update()
{
    currentState->update();


}

void StateController::setCommand(int type, int com)
{
    if (type == 1)
    {
        if (com == 1)
        {
            trySetNewState(STATE::STANDUP);
        } else if (com == 2)
        {
            trySetNewState(STATE::LAYDOWN);
        } else if (com == 3)
        {
            trySetNewState(STATE::STEP);
        }

    }
    if (type == 2)
    {
        if (com == 1)
        {
            GRAPH()->play();

        } else if (com == 2)
        {
            GRAPH()->pauze();

        } else if (com == 3)
        {
            trySetNewState(STATE::TESTALLLEGSDOWN);

        } else if (com == 4)
        {
            trySetNewState(STATE::TEST2LEGSUP);

        }

    }
   // ci::app::console() << "command " << type << " " << com << std::endl;

}

void StateController::trySetNewState(STATE state)
{

    auto it = find_if(states.begin(), states.end(), [&, state](const std::shared_ptr<BaseState> &obj)
    { return obj->state == state; });

    bool setNewState = true;
    std::string error = "";
    if (!currentState->isDone())
    {
        setNewState = false;
        error = "current state (" + currentState->getName() + ") busy";

    } else if (state == currentState->state  && !currentState->canRepeat() )
    {
        setNewState = false;
        error = "already in state " + currentState->getName();
    } else if (!currentState->canHaveNextState(state))
    {
        setNewState = false;
        error = "can't go from " + currentState->getName() + " to " + it->get()->getName();
    }


    if (setNewState)
    {
        STATUS()->soundHandler.play(SOUND::BEEP);
        STATUS()->log("set new state " + it->get()->getName());
        currentState = *it;
        currentState->start();


    } else
    {
        STATUS()->soundHandler.play(SOUND::ERROR);
        STATUS()->logWarning(error);

    }


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
        ImGui::TextColored(ImVec4(0, 1, 0, 1), "FREE");
    } else
    {
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "BUSY");
    }


    ImGui::Separator();
    bool forceDisable = false;
    if (!currentState->isDone())
    {
        forceDisable = true;
    }

    for (int i = 0; i < states.size(); i++)
    {
        ImGui::PushID(i);

        bool disable = true;
        if (!forceDisable)
        {
            if (currentState->state != states[i]->state ||  currentState->canRepeat())
            {
                if (currentState->canHaveNextState(states[i]->state))
                {
                    disable = false;
                }
            }
        }

        if (disable)
        {

            ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);

        }
        if (ImGui::Button(states[i]->getName().c_str(), ImVec2(150.f, 0.0f)))
        {
            trySetNewState(states[i]->state);
        }
        if (disable)
        {
            ImGui::PopItemFlag();
            ImGui::PopStyleVar();

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