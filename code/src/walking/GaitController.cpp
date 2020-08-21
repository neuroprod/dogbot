//
// Created by kris on 20.08.20.
//

#include "GaitController.h"
#include <imgui/imgui.h>
#include "../RobotSettings.h"
using namespace ci;
using namespace ci::app;
using namespace std;
void GaitController::setup()
{
    LegControllerRef fr =LegController::create();
    fr->setup(vec3(BOTSETTINGS()->bodyLength / 2 +BOTSETTINGS()->hipOffsetX, 0, BOTSETTINGS()->bodyWidth / 2 + BOTSETTINGS()->hipOffsetZ));
    LegControllerRef fl=LegController::create();
    fl->setup(vec3(BOTSETTINGS()->bodyLength / 2 + BOTSETTINGS()->hipOffsetX, 0, -BOTSETTINGS()->bodyWidth / 2- BOTSETTINGS()->hipOffsetZ));
    LegControllerRef br=LegController::create();
    br->setup(  vec3(-BOTSETTINGS()->bodyLength / 2 - BOTSETTINGS()->hipOffsetX, 0, BOTSETTINGS()->bodyWidth / 2 + BOTSETTINGS()->hipOffsetZ));
    LegControllerRef bl=LegController::create();
    bl->setup(vec3(-BOTSETTINGS()->bodyLength / 2 - BOTSETTINGS()->hipOffsetX, 0, -BOTSETTINGS()->bodyWidth / 2 - BOTSETTINGS()->hipOffsetZ));

    legs.push_back(fr);
    legs.push_back(fl);
    legs.push_back(br);
    legs.push_back(bl);

    //vv debug stuff
    currentLeg = fr;
    if(debug) currentLeg->debug =true;
    camera.setBodyPos(currentLeg->homePos);
    drawBatches.makeHome();
}
void GaitController::reset()
{
    previousTime = getElapsedSeconds();
    stepTimeTotal =stepInput.stepTime;
    currentStepTime = stepTimeTotal;

    legs[0]->state =3;
    legs[1]->state =1;
    legs[2]->state =1;
    legs[3]->state =3;

    //next step is update stepState

}
void GaitController::update()
{
    double currentTime = getElapsedSeconds();
    float delta =(currentTime - previousTime) *1000;
    previousTime =currentTime;
    currentStepTime+=delta;
    if(currentStepTime> stepTimeTotal)//switch internal stepStates
    {

        currentStepTime-= stepTimeTotal;
        stepTimeTotal =stepInput.stepTime;
        for(int i=0;i<4;i++)
        {
            legs[i]->setNextState();
            int state = legs[i]->state;
            if(state==0)//goUpHome
            {
                legs[i]->currentSpline = getHomeRise(stepInput,legs[i]);
               //adj HomePos;
            }
            if(state==1)//godown
            {
                legs[i]->currentSpline = getWalkFall(stepInput,legs[i]);

            }
            if(state==2)//gohome
            {
                legs[i]->currentSpline = getHomeStep(stepInput,legs[i]);

            }
            if(state==3)//goWalk
            {
                legs[i]->currentSpline = getWalkStep(stepInput,legs[i]);
            }

        }
    }

    for(int i=0;i<4;i++)
    {
        legs[i]->update( currentStepTime/stepTimeTotal);

    }



}
BSpline3f GaitController::getWalkStep(StepInput &stepInput,LegControllerRef legController)
{
    //update input
    legController->stepHeight =stepInput.stepHeight;
    legController->moveAngle=stepInput.moveAngle;
    legController->moveLength =stepInput.moveLength;
    legController->rotAngle =stepInput.rotAngle;


    int numSteps =20;//subdev to get smooth circl
    float stepAdj = 1.f/numSteps;
    float currentStepPos =0;


    vec3 moveVec =vec3(cos(legController->moveAngle),0,sin(legController->moveAngle))*legController->moveLength;


    float homeRadius =glm::length(legController->homePos);
    float angleStep = legController->rotAngle * stepAdj;
    float currentAngle = atan2(legController->homePos.z,legController->homePos.x);
    vector<vec3> mPoints;

    for(int i=0;i<=numSteps;i++)
    {
        vec3 movePos =  legController->homePos -moveVec*currentStepPos;
        vec3 turnPos = vec3(cos( currentAngle ), 0, sin( currentAngle ))*homeRadius -legController->homePos;
        mPoints.push_back(turnPos +movePos);

        currentAngle += angleStep;
        currentStepPos +=stepAdj;
    }


    BSpline3f spline(mPoints, 3, false, true);

    return spline;

}

BSpline3f GaitController::getHomeStep(StepInput &stepInput,LegControllerRef legController)
{

    int numSteps =20; //subdev to get smooth circle
    float stepAdj = 1.f/numSteps;
    float currentStepPos =1;


    vec3 moveVec =vec3(cos(legController->moveAngle),0,sin(legController->moveAngle))*legController->moveLength;


    float homeRadius =glm::length(legController->homePos);
    float angleStep = legController->rotAngle * stepAdj;
    float currentAngle = atan2(legController->homePos.z,legController->homePos.x) -legController->rotAngle;
    vector<vec3> mPoints;

    for(int i=0;i<=numSteps;i++)
    {
        vec3 movePos =  legController->homePos +moveVec*currentStepPos;
        vec3 turnPos = vec3(cos( currentAngle ), 0, sin( currentAngle ))*homeRadius -legController->homePos;
        mPoints.push_back(turnPos +movePos);

        currentAngle += angleStep;
        currentStepPos -=stepAdj;
    }


    BSpline3f spline(mPoints, 3, false, true);

    return spline;

}
BSpline3f GaitController::getHomeRise(StepInput &stepInput,LegControllerRef legController)
{

    vector<vec3> mPoints;

    //getStartPoint
    vec3 moveVec =vec3(cos(legController->moveAngle),0,sin(legController->moveAngle))*legController->moveLength;
    float homeRadius =glm::length(legController->homePos);
    float currentAngle = atan2(legController->homePos.z,legController->homePos.x) +legController->rotAngle;
    vec3 startPoint =   vec3(cos( currentAngle ), 0, sin( currentAngle ))*homeRadius -moveVec;





    // update homePos
    legController->setHomePosOffzet(vec3(0,0,stepInput.homeZOffset));



    vec3 endPoint=vec3( legController->homePos +vec3(0,legController->stepHeight,0));


    vec3 midPoint=(startPoint+endPoint)/2.f;


    mPoints.push_back( startPoint);
    mPoints.push_back( midPoint);
    mPoints.push_back( endPoint);


    BSpline3f spline(mPoints, 2, false, true);


    return spline;

}


BSpline3f GaitController::getWalkFall(StepInput &stepInput,LegControllerRef legController)
{


    vector<vec3> mPoints;

    vec3 startPoint =vec3( legController->homePos +vec3(0,legController->stepHeight,0));

    //update input
    legController->stepHeight =stepInput.stepHeight;
    legController->moveAngle=stepInput.moveAngle;
    legController->moveLength =stepInput.moveLength;
    legController->rotAngle =stepInput.rotAngle;



    vec3 moveVec =vec3(cos(legController->moveAngle),0,sin(legController->moveAngle))*legController->moveLength;
    float homeRadius =glm::length(legController->homePos);
    float currentAngle = atan2(legController->homePos.z,legController->homePos.x) -stepInput.rotAngle;
    vec3 endPoint =   vec3(cos( currentAngle ), 0, sin( currentAngle ))*homeRadius +moveVec;



    vec3 midPoint =(startPoint +endPoint)/2.f;

    mPoints.push_back( startPoint);
    mPoints.push_back( midPoint);
    mPoints.push_back( endPoint);

    BSpline3f spline(mPoints, 2, false, true);

    return spline;

}

void GaitController::drawGui()
{

    ImGui::Begin("GaitController");
    stepInput.drawGui(false);
    ImGui::Separator();
    ImGui::Checkbox("debug", &debug);

    if(debug)
    {
        ImGui::Combo("leg", &leg_combo, "FR\0FL\0BR\0BL\0\0");
        if (leg_combo_current != leg_combo)
        {
            leg_combo_current = leg_combo;
            currentLeg = legs[leg_combo_current];
            camera.setBodyPos(currentLeg->homePos);
        }


        vMin = ImGui::GetWindowContentRegionMin();
        vMax = ImGui::GetWindowContentRegionMax();

        int widthNew = vMax.x - vMin.x;

        bool needResize = false;
        if (widthNew != fboWidth)
        {
            needResize = true;
            fboWidth = widthNew;


        }
        if (needResize)
        {
            gl::Fbo::Format format;
            format.setSamples(4);
            mFbo = gl::Fbo::create(fboWidth, fboWidth, format.depthTexture());
        }

        mFbo->bindFramebuffer();

        gl::clear(Color(0.2, 0.2f, 0.2f));


        gl::viewport(ivec2(0), mFbo->getSize());
        gl::setMatricesWindow(mFbo->getSize(), true);

        //draw
        gl::pushMatrices();
        camera.aspect = 1;

        camera.targetCameraDistance = 500;
        camera.cameraDistance = camera.targetCameraDistance;
        camera.update(vMin, vMax);
        gl::setMatrices(camera.mCam);


        gl::drawCoordinateFrame(100, 0, 0);

        gl::pushMatrices();
        gl::translate(currentLeg->homePos);
        gl::color(0.3, 0.3, 0.3);
        drawBatches.homeBatch->draw();
        gl::popMatrices();

        gl::color(1.0, 1.0, 1.0);
        currentLeg->draw();

        gl::popMatrices();
        mFbo->unbindFramebuffer();




        // camera.drawGui();


        ImGui::SliderFloat("current stepTime", &currentStepTime, 0, stepTimeTotal);
        ImVec2 uv_min = ImVec2(0.0f, 1.0f);                 // Top-left
        ImVec2 uv_max = ImVec2(1.0f, 0.0f);                 // Lower-right
        ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
        ImVec4 border_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // 50% opaque white
        ImGui::Image((void *) (intptr_t) mFbo->getColorTexture()->getId(), ImVec2(fboWidth, fboWidth), uv_min, uv_max,
                     tint_col, border_col);


        ImGui::End();


    }

};
