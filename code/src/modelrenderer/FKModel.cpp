#include "FKModel.h"
#include "cinder/gl/gl.h"

#include "MeshDataPool.h"
#include "../RobotSettings.h"

using namespace ci;
using namespace ci::app;
using namespace std;



void FKModel::setup() {

	

	root = FKNode::create("root","root");


	build();
	root->update();
}

void FKModel::setPosition(mat4 bodyMatrix,vector<float> &jointAngles) 
{
	body->baseMatrix = bodyMatrix;
	for (int i = 0; i < legs.size(); i++)
	{
		int index = i * 3;
		auto FKleg = legs[i];

		FKleg->hip->setRotation(jointAngles[index]);
		FKleg->knee->setRotation(jointAngles[index+1]);
		FKleg->ankle->setRotation(jointAngles[index+2]);
	}
}


void FKModel::update() 
{

	root->update();
}
void FKModel::build()
{




	nodes.clear();
	legs.clear();
	root->removeAllChildren();
	nodes.push_back(root);

	body = FKNode::create("body", "body");
	body->setBase(vec3(0, 0, 0));
	nodes.push_back(body);
	root->addChild(body);



	FRLeg = FKLeg::create();
	FRLeg->setup("FR",body, vec3(  BOTSETTINGS()->bodyLength / 2, 0, BOTSETTINGS()->bodyWidth / 2), nodes);
	legs.push_back(FRLeg);

	FLLeg = FKLeg::create();
	FLLeg->setup("FL", body, vec3(  BOTSETTINGS()->bodyLength / 2, 0, -BOTSETTINGS()->bodyWidth / 2), nodes);
	legs.push_back(FLLeg);

	BRLeg = FKLeg::create();
	BRLeg->setup("BR", body, vec3(-  BOTSETTINGS()->bodyLength / 2, 0, BOTSETTINGS()->bodyWidth / 2), nodes);
	legs.push_back(BRLeg);

	BLLeg = FKLeg::create();
	BLLeg->setup("BL", body, vec3(-  BOTSETTINGS()->bodyLength / 2, 0, -BOTSETTINGS()->bodyWidth / 2), nodes);
	legs.push_back(BLLeg);


}

void FKModel::drawWire()
{
    for (auto n : nodes)
    {
       n->setGlobalPos();

    }
    gl::lineWidth(2);
    gl::color(1,1,1);
    gl::begin(GL_LINES);

    gl::vertex( FRLeg->hip->globalPos);
    gl::vertex( BRLeg->hip->globalPos);

    gl::vertex( FLLeg->hip->globalPos);
    gl::vertex( BLLeg->hip->globalPos);


    gl::vertex( FRLeg->hip->globalPos);
    gl::vertex( FLLeg->hip->globalPos);

    gl::vertex( BRLeg->hip->globalPos);
    gl::vertex( BLLeg->hip->globalPos);

    for (auto l : legs)
    {
        gl::vertex( l->hip->globalPos);
        gl::vertex( l->knee->globalPos);

        gl::vertex( l->knee->globalPos);
        gl::vertex( l->ankle->globalPos);

        gl::vertex( l->ankle->globalPos);
        vec3 foot=  l->ankle->globalMatrix *vec4(0,-BOTSETTINGS()->underLegLength+BOTSETTINGS()->footRadius,0,1);
        gl::vertex(foot);

    }

    gl::end();
    gl::lineWidth(1);
    gl::color(0,0,0);
    for (auto l : legs)
    {

        vec3 foot=  l->ankle->globalMatrix *vec4(0,-BOTSETTINGS()->underLegLength+BOTSETTINGS()->footRadius,0,1);
       gl::drawSphere(foot,BOTSETTINGS()->footRadius);

    }

}