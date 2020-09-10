#include "FKModel.h"
#include "cinder/gl/gl.h"

#include "SymbolBatches.h"
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
    bodyPos = bodyMatrix * vec4(0,0,0,1);

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
    body->setMass(BOTSETTINGS()->bodyMass,BOTSETTINGS()->bodyCOM);
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
void FKModel::calcCOM()
{
    COM.x =0;
    COM.y =0;
    COM.z=0;
    totalMass =0;
    for (auto n : nodes)
    {
        n->calcCOM();
        COM += (n->globalCOM *n->mMass);
        totalMass+=n->mMass;
    }
    COM/= totalMass;

}
void FKModel::drawCOM()
{
    calcCOM();
    gl::color(0,1,1);
    gl::pushMatrices();
    gl::translate(COM);
    gl::scale(vec3( std::cbrt(totalMass)*10));
    SYMBOLBATCHES()->sphereBatch->draw();
    gl::popMatrices();

    gl::color(0,0,1);
    for (auto n : nodes)
    {


        gl::pushMatrices();
        gl::translate(n->globalCOM);
        gl::scale(vec3( std::cbrt(n->mMass)*10));
        SYMBOLBATCHES()->sphereBatch->draw();
        gl::popMatrices();
    }


    nodes[5]->calcGlobalPos();
    vec3 posFR = nodes[5]->globalPos;
    posFR.y-=BOTSETTINGS()->footRadius;
    nodes[9]->calcGlobalPos();
    vec3 posFL = nodes[9]->globalPos;
    posFL.y-=BOTSETTINGS()->footRadius;
    nodes[13]->calcGlobalPos();
    vec3 posBR = nodes[13]->globalPos;
    posBR.y-=BOTSETTINGS()->footRadius;
    nodes[17]->calcGlobalPos();
    vec3 posBL = nodes[17]->globalPos;
    posBL.y-=BOTSETTINGS()->footRadius;

    vec3 c1 =  (posFR+posBL)/2.f;
    vec3 c1R = c1;
    c1R.y+=300;

    gl::color(1,1,1);
    gl::begin(GL_LINES);

    gl::vertex( posFR);
    gl::vertex( posBL);

    gl::vertex( posFL);
    gl::vertex( posBR);

    gl::vertex( c1);
    gl::vertex( c1R);

    gl::end();
}
void FKModel::drawWire()
{
    for (auto n : nodes)
    {
       n->calcGlobalPos();

    }
    gl::lineWidth(1);
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

        gl::vertex(l->toe->globalPos);

    }

    gl::end();
    gl::lineWidth(1);
    gl::enableAlphaBlending(true);
    gl::color(1,1,1,0.2);
    for (auto l : legs)
    {

        vec3 foot=  l->toe->globalPos;
        gl::pushMatrices();
        gl::translate(foot);
        gl::scale(vec3(BOTSETTINGS()->footRadius));
        SYMBOLBATCHES()->sphereBatch->draw();
        gl::popMatrices();
    }
    gl::enableAlphaBlending(false);
}