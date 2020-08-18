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


}