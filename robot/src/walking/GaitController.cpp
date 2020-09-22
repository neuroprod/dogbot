//
// Created by kris on 20.08.20.
//

#include "GaitController.h"
#include <imgui/imgui.h>
#include "../RobotSettings.h"
#include "../graph/GraphRenderer.h"
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
    if(editGate) currentLeg->debug =true;
    camera.setBodyPos(currentLeg->homePos);




    gaitGraph.prepGraph("Gait","simulation",4,{1,1,1,1},{Color(1,0,0),Color(0,1,0),Color(0,0,1),Color(1,1,1)},{"DerX","DerY","DerZ","Speed"} );
    gaitGraph.gVisible =false;
    GRAPH()->reg(&gaitGraph);
}
void GaitController::reset()
{
    previousTime = getElapsedSeconds();
    stepTimeTotal =stepInput.stepTime;
    currentStepTime = stepTimeTotal;

    legs[0]->state =3;
    legs[0]->reset();
    legs[1]->state =1;
    legs[1]->reset();
    legs[2]->state =1;
    legs[2]->reset();
    legs[3]->state =3;
    legs[3]->reset();

    //next step is update stepState

}
void GaitController::update()
{

    double currentTime = getElapsedSeconds();
    delta =(currentTime - previousTime) *1000;

    delta =1000.f/120.f;

    previousTime =currentTime;
    currentStepTime+=delta;
    if(currentStepTime> stepTimeTotal)//switch internal stepStates
    {
        int state = legs[0]->state;
        if(state==3 || state==1)
        {
            GRAPH()->pulse(1);
        }else{
            GRAPH()->pulse(2);
        }
        currentStepTime-= stepTimeTotal;
        stepTimeTotal =stepInput.stepTime;
        for(int i=0;i<4;i++)
        {
            legs[i]->setNextState();
            int state = legs[i]->state;
            legs[i]->prevSpline=legs[i]->currentSpline;


            if(state==0)//goUpHome
            {
                legs[i]->currentSpline = getHomeRise(stepInput,legs[i]);
               //adj HomePos;
            }
            if(state==1)//godown
            {
                legs[i]->currentSpline = getWalkFall(stepInput,legs[i]);
                legs[i]->nextSpline  =getHomeStep(stepInput,legs[i]);
            }
            if(state==2)//gohome
            {
                legs[i]->currentSpline = getHomeStep(stepInput,legs[i]);

            }
            if(state==3)//goWalk
            {
                legs[i]->currentSpline = getWalkStep(stepInput,legs[i]);
            }
            legs[i]->prepStateSwitch();
        }
    }else
        {
        GRAPH()->pulse(0);

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

    vec3 moveDir = vec3(cos(legController->moveAngle),0,sin(legController->moveAngle));
    float homeAngle = atan2(legController->homePos.z,legController->homePos.x);
    float homeRadius =glm::length(legController->homePos);

    //getStartPoint
    vec3 moveVec =moveDir*legController->moveLength;
    float currentAngle = homeAngle  +legController->rotAngle;
    vec3 startPoint =   vec3(cos( currentAngle ), 0, sin( currentAngle ))*homeRadius -moveVec;

    float stepDistance =glm::length(startPoint- legController->homePos);


    // get "prev" point
    vec3 prevMoveVec =vec3(cos(legController->moveAngle),0,sin(legController->moveAngle))*legController->moveLength*0.999f;
    float prevAngle = atan2(legController->homePos.z,legController->homePos.x) +legController->rotAngle*0.999f;
    vec3 prevPoint =   vec3(cos( prevAngle ), 0, sin( prevAngle ))*homeRadius -prevMoveVec;

    vec3 dirIn =startPoint-prevPoint  ;
    if(glm::length2(dirIn)!=0)
    {
        dirIn = glm::normalize(dirIn);

    }


    // update homePos
    legController->setHomePosOffzet(vec3(0,0,stepInput.homeZOffset));


    vec3 risingInPoint = startPoint + dirIn*stepDistance*walkRisingIn;

    vec3 endPoint=vec3( legController->homePos +vec3(0,legController->stepHeight,0));
    vec3 midPoint=vec3(lerp(startPoint.x,endPoint.x,walkRisingMidX),legController->stepHeight*walkRisingMidY,lerp(startPoint.z,endPoint.z,walkRisingMidX));


    //rising out
    vec3 stepDirNew = startPoint -endPoint;
    stepDirNew.y =0;
    float stepDistanceNew =glm::length(stepDirNew);

    vec3 dirOut =  endPoint-midPoint;
    dirOut.y =0;
    if(dirOut.x!=0 || dirOut.z!=0)dirOut = normalize(dirOut);
    vec3 risingOutPoint = endPoint- dirOut*stepDistanceNew *walkRisingOut;
    //save dir for faling
    legController->dirStartFalling =dirOut*stepDistanceNew*walkFalingIn;

    mPoints.push_back( startPoint);
    mPoints.push_back(risingInPoint );
    mPoints.push_back( midPoint);
    mPoints.push_back(risingOutPoint );
    mPoints.push_back( endPoint);


    BSpline3f spline(mPoints, 3, false, true);


    return spline;

}


BSpline3f GaitController::getWalkFall(StepInput &stepInput,LegControllerRef legController)
{


    vector<vec3> mPoints;

    vec3 startPoint =vec3( legController->homePos +vec3(0,legController->stepHeight,0));
    vec3 fallingInPoint = startPoint+ legController->dirStartFalling;
    //update input
    legController->stepHeight =stepInput.stepHeight;
    legController->moveAngle=stepInput.moveAngle;
    legController->moveLength =stepInput.moveLength;
    legController->rotAngle =stepInput.rotAngle;


    vec3 moveDir = vec3(cos(legController->moveAngle),0,sin(legController->moveAngle));
    float homeAngle = atan2(legController->homePos.z,legController->homePos.x);
    float homeRadius =glm::length(legController->homePos);



    vec3 moveVec =moveDir *legController->moveLength;
    float currentAngle = homeAngle -stepInput.rotAngle;
    vec3 endPoint =   vec3(cos( currentAngle ), 0, sin( currentAngle ))*homeRadius +moveVec;

    vec3 nextMoveVec =vec3(cos(legController->moveAngle),0,sin(legController->moveAngle))*legController->moveLength*0.999f;
    float nextAngle = atan2(legController->homePos.z,legController->homePos.x) +legController->rotAngle*0.999f;
    vec3 nextPoint =   vec3(cos(  nextAngle ), 0, sin(  nextAngle ))*homeRadius -nextMoveVec;

    vec3 dirOut =endPoint -nextPoint  ;
    if(glm::length2(dirOut )!=0)
    {
        dirOut = glm::normalize(dirOut );
    }

    vec3 fallingOutPoint = endPoint + dirOut*glm::length( endPoint)*walkFalingOut;

    vec3 midPoint=vec3(lerp(startPoint.x,endPoint.x,walkFalingMidX),legController->stepHeight*walkFalingMidY,lerp(startPoint.z,endPoint.z,walkFalingMidX));

    mPoints.push_back( startPoint);
    mPoints.push_back( fallingInPoint );
    mPoints.push_back( midPoint);
    mPoints.push_back(  fallingOutPoint);
    mPoints.push_back( endPoint);

    BSpline3f spline(mPoints, 3, false, true);

    return spline;

}

void GaitController::drawGui()
{

    ImGui::Begin("GaitController");
    stepInput.drawGui(false);
    ImGui::Separator();

    ImGui::Checkbox("edit Gait", &editGate);
    if(editGate)
    {
    if ( ImGui::DragFloat("walkRisingIn", &walkRisingIn,0.01,0,1));
    if ( ImGui::DragFloat("walkRisingOut", &walkRisingOut, 0.01, 0, 1));
    if ( ImGui::DragFloat("walkRisingMidX", &walkRisingMidX, 0.01, 0, 1));
    if ( ImGui::DragFloat("walkRisingMidY", &walkRisingMidY, 0.01, 0, 1));

    ImGui::Separator();
    if ( ImGui::DragFloat("walkFalingIn", &walkFalingIn, 0.01, 0, 1));
    if ( ImGui::DragFloat("walkFalingOut", &walkFalingOut, 0.01, 0, 1));
    if ( ImGui::DragFloat("walkFalingMidX", &walkFalingMidX, 0.01, 0, 1));
    if ( ImGui::DragFloat("walkFalingMidY", &walkFalingMidY, 0.01, 0, 1));
    ImGui::Separator();



        vec3 graphDir = currentLeg->targetPos -currentLeg->prevTargetPos;
        float l = glm::length(graphDir)*delta;
        graphDir = glm::normalize(graphDir);
        gaitGraph.addData({  graphDir.x*90, graphDir.y*90,graphDir.z*90,(l-35)*5});


        ImGui::Combo("leg", &leg_combo, "FR\0FL\0BR\0BL\0\0");
        if (leg_combo_current != leg_combo)
        {
            leg_combo_current = leg_combo;
            if(currentLeg)currentLeg->debug =false;

            currentLeg = legs[leg_combo_current];
            currentLeg->debug =true;


        }

        camera.setBodyPos(currentLeg->homePos +vec3(0,currentLeg->stepHeight/2,0));
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

        camera.targetCameraDistance = 300;
        camera.cameraDistance = camera.targetCameraDistance;
        camera.update(vMin, vMax);
        gl::setMatrices(camera.mCam);




        gl::pushMatrices();
        gl::translate(currentLeg->homePos);
        gl::drawCoordinateFrame(50, 0, 0);

        gl::popMatrices();

        gl::color(1.0, 1.0, 1.0);
        currentLeg->draw();

        gl::popMatrices();
        mFbo->unbindFramebuffer();




        // camera.drawGui();



        ImVec2 uv_min = ImVec2(0.0f, 1.0f);                 // Top-left
        ImVec2 uv_max = ImVec2(1.0f, 0.0f);                 // Lower-right
        ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
        ImVec4 border_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // 50% opaque white
        ImGui::Image((void *) (intptr_t) mFbo->getColorTexture()->getId(), ImVec2(fboWidth, fboWidth), uv_min, uv_max,
                     tint_col, border_col);





    }
    ImGui::End();
};
