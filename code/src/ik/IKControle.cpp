#include "IKControle.h"
#include "cinder/CinderImGui.h"
#include "../RobotSettings.h"
using namespace ci;
using namespace ci::app;
using namespace std;


void IKControle::setup()
{
    angles.resize(12);
    model.setup();

	FR = IKControleLeg::create();
	FL = IKControleLeg::create();
	BR = IKControleLeg::create();
	BL = IKControleLeg::create();

	legs.push_back(FR);
	legs.push_back(FL);
	legs.push_back(BR);
	legs.push_back(BL);

	setBase();

}

void IKControle::setBase()
{
	bodyX =BOTSETTINGS()->bodyXStart;;
	bodyY = BOTSETTINGS()->bodyYStart;
	bodyZ = 0;

	bodyRotX = 0;
	bodyRotY = 0;
	bodyRotZ = 0;


	FR->homePos = FR->targetPos = vec3(BOTSETTINGS()->bodyLength / 2 +BOTSETTINGS()->hipOffsetX, 0, BOTSETTINGS()->bodyWidth / 2 + BOTSETTINGS()->hipOffsetZ);
	FL->homePos = FL->targetPos = vec3(BOTSETTINGS()->bodyLength / 2 + BOTSETTINGS()->hipOffsetX, 0, -BOTSETTINGS()->bodyWidth / 2- BOTSETTINGS()->hipOffsetZ);
	BR->homePos = BR->targetPos = vec3(-BOTSETTINGS()->bodyLength / 2 - BOTSETTINGS()->hipOffsetX, 0, BOTSETTINGS()->bodyWidth / 2 + BOTSETTINGS()->hipOffsetZ);
	BL->homePos = BL->targetPos = vec3(-BOTSETTINGS()->bodyLength / 2 - BOTSETTINGS()->hipOffsetX, 0, -BOTSETTINGS()->bodyWidth / 2 - BOTSETTINGS()->hipOffsetZ);

	

}
void IKControle::update()
{
    bodyMatrix = mat4();
    bodyMatrix = glm::translate(bodyMatrix, vec3(bodyX, bodyY, bodyZ));

    bodyMatrix = glm::rotate(bodyMatrix, bodyRotX, vec3(1, 0, 0));
    bodyMatrix = glm::rotate(bodyMatrix, bodyRotY, vec3(0, 1, 0));
    bodyMatrix = glm::rotate(bodyMatrix, bodyRotZ, vec3(0, 0, 1));

   mat4 invBodyMatrix = glm::inverse(bodyMatrix);
    int count = 0;
    for (int i=0; i< legs.size();i++)
    {
        vec3 target = legs[i]->targetPos;
        target.y += BOTSETTINGS()->footRadius;
        model.legs[i]->resolve(target, invBodyMatrix);

        angles[count++] = model.legs[i]->angleHip1;
        angles[count++] = model.legs[i]->angleHip2;
        angles[count++] = model.legs[i]->angleKnee;
    }


}

void IKControle::drawGui()
{

    ImGui::Begin("IKControle");





    ImGui::DragFloat("body X", &bodyX, 1, -100, 100) ;
    ImGui::DragFloat("body Y", &bodyY, 1, 0, 700);
    ImGui::DragFloat("body Z", &bodyZ, 1, -100, 100);

    ImGui::DragFloat("body rotX", &bodyRotX, 0.01, -3.1415, 3.1415);
    ImGui::DragFloat("body rotY", &bodyRotY, 0.01, -3.1415, 3.1415) ;
    ImGui::DragFloat("body rotZ", &bodyRotZ, 0.01, -3.1415, 3.1415) ;
	if (ImGui::Button("resetBody"))
	{
		bodyRotX = 0;
		bodyRotY =0;
		bodyRotZ = 0;
		bodyX = 0;
		bodyY = BOTSETTINGS()->bodyY;
		bodyZ = 0;
	}
    ImGui::Separator();
    ImGui::DragFloat3("FR Target", &FR->targetPos[0], 1.f,-1000, 1000);
    ImGui::DragFloat3("FL Target", &FL->targetPos[0], 1.f, -1000, 1000);

    ImGui::DragFloat3("BR Target", &BR->targetPos[0], 1.f, -1000, 1000);
    ImGui::DragFloat3("BL Target", &BL->targetPos[0], 1.f, -1000, 1000);
	if (ImGui::Button("resetTargets"))
	{
	
		FR->targetPos = FR->homePos;
		FL->targetPos = FL->homePos;
		BR->targetPos = BR->homePos;
		BL->targetPos = BL->homePos;
	
	}
	if (ImGui::Button("resetAll"))
	{

		FR->targetPos = FR->homePos;
		FL->targetPos = FL->homePos;
		BR->targetPos = BR->homePos;
		BL->targetPos = BL->homePos;
		bodyRotX = 0;
		bodyRotY = 0;
		bodyRotZ = 0;
		bodyX = 0;
		bodyY = BOTSETTINGS()->bodyY;
		bodyZ = 0;


	}
    ImGui::Separator();
	float toDeg = 180./3.1415;

	ImGui::Text("FR  H:%f K:%f A:%f", angles[0]*toDeg ,angles[1]*toDeg,angles[2]*toDeg );
    ImGui::Text("FL  H:%f K:%f A:%f", angles[3]*toDeg ,angles[4]*toDeg,angles[5]*toDeg );
    ImGui::Text("BR  H:%f K:%f A:%f", angles[6]*toDeg ,angles[7]*toDeg,angles[8]*toDeg );
    ImGui::Text("FL  H:%f K:%f A:%f", angles[9]*toDeg ,angles[10]*toDeg,angles[11]*toDeg );

	ImGui::End();
}