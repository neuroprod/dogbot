#include "IKModel.h"
#include "../RobotSettings.h"
using namespace ci;
using namespace ci::app;
using namespace std;

void IKModel::setup()
{


	reBuild();

}
void IKModel::reBuild() 
{
	legs.clear();

	FR = IKLeg::create();
    FR->setupPos(vec3(  BOTSETTINGS()->bodyLength / 2, 0, BOTSETTINGS()->bodyWidth / 2));



	FL = IKLeg::create();
    FL->setupPos(vec3(  BOTSETTINGS()->bodyLength / 2, 0, -BOTSETTINGS()->bodyWidth / 2));
	FL->isLeft = true;

	BR = IKLeg::create();
    BR->setupPos( vec3(  -BOTSETTINGS()->bodyLength / 2, 0, BOTSETTINGS()->bodyWidth / 2));


	BL = IKLeg::create();
    BL->setupPos(vec3(-  BOTSETTINGS()->bodyLength / 2, 0, -BOTSETTINGS()->bodyWidth / 2));
	BL->isLeft = true;




	legs.push_back(FR);
	legs.push_back(FL);
	legs.push_back(BR);
	legs.push_back(BL);

}
void IKModel::update()
{

/*
	bodyMatrix = mat4();
	bodyMatrix = glm::translate(bodyMatrix, vec3(controle->bodyX, controle->bodyY, controle->bodyZ));

	bodyMatrix = glm::rotate(bodyMatrix, controle->bodyRotX, vec3(1, 0, 0));
	bodyMatrix = glm::rotate(bodyMatrix, controle->bodyRotY, vec3(0, 1, 0));
	bodyMatrix = glm::rotate(bodyMatrix, controle->bodyRotZ, vec3(0, 0, 1));

	mat4 invBodyMatrix = glm::inverse(bodyMatrix);
	int count = 0;
	for (int i=0; i< controle->legs.size();i++) 
	{
		vec3 target = controle->legs[i]->targetPos;
		target.y += config->footRadius;
		legs[i]->resolve(target, invBodyMatrix);

		angles[count++] = legs[i]->angleHip1;
		angles[count++] = legs[i]->angleHip2;
		angles[count++] = legs[i]->angleKnee;
	}
*/
}