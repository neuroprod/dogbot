#include "FKLeg.h"
#include "../RobotSettings.h"

using namespace ci;
using namespace ci::app;
using namespace std;
FKLegRef FKLeg::create()
{
	FKLegRef ref = std::make_shared<FKLeg>();
	return ref;
}

void FKLeg::setup(string name,FKNodeRef body, glm::vec3 pos, std::vector<FKNodeRef> &nodes)
{

	float  PI = glm::pi<float>();

	hipOffsetZFlip = 1;
	if (pos.x < 0 && pos.z>0)hipOffsetZFlip = -1;
	if (pos.x > 0 && pos.z<0)hipOffsetZFlip = -1;


	if (hipOffsetZFlip == 1)
	{
		hip = FKNode::create(name + "hip", "hip");
	}
	if (hipOffsetZFlip == -1)
	{
		hip = FKNode::create(name + "hip", "hip_mirror");
	}
	float hip1Rot = 0;
	if (pos.x < 0)hip1Rot = PI;
	hip->setBase(pos,  vec3(0,hip1Rot,0));
   hip->setMass(BOTSETTINGS()->hipMass,BOTSETTINGS()->hipCOM);
	body->addChild(hip);
	body->update();



	knee = FKNode::create(name+"knee", "knee");
    knee->setBase(vec3(BOTSETTINGS()->hipOffsetX,0 , BOTSETTINGS()->hipOffsetZ*hipOffsetZFlip),vec3(0, -PI/2* hipOffsetZFlip,0));
    knee->setMass(BOTSETTINGS()->kneeMass,BOTSETTINGS()->kneeCOM);
    hip->addChild(knee);



	ankle = FKNode::create(name+"ankle", "ankle");
	ankle->setBase(vec3(0, -BOTSETTINGS()->upperLegLength, 0), vec3(0, 0, 0));
   ankle->setMass(BOTSETTINGS()->ankleMass,BOTSETTINGS()->ankleCOM);
	knee->addChild(ankle);

    toe= FKNode::create(name+" toe", " toe");
    toe->setBase(vec3(0, -BOTSETTINGS()->underLegLength+BOTSETTINGS()->footRadius, 0), vec3(0, 0, 0));
    toe->setMass(BOTSETTINGS()->toeMass,BOTSETTINGS()->toeCOM);
    ankle->addChild(toe);

	nodes.push_back(hip);
	nodes.push_back(knee);
	nodes.push_back(ankle);
    nodes.push_back(toe);

	



}

