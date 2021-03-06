#pragma once
#include "cinder/app/App.h"
#include "FKNode.h"
#include "FKLeg.h"




class FKModel;
typedef std::shared_ptr<FKModel> FKModelRef;

class FKModel
{
public:
	FKModel() {};
	void setup();
    void build();

	void setPosition(glm::mat4 bodyMatrix, std::vector<float> &jointAngles);

	void update();

    void calcCOM();
    void drawCOM();
    void drawWire();

    ci::vec3 COM =ci::vec3(0);
    float totalMass;

	FKNodeRef root;
	FKNodeRef body;

	FKLegRef FRLeg;
	FKLegRef FLLeg;

	FKLegRef BRLeg;
	FKLegRef BLLeg;

	std::vector<FKNodeRef> nodes;
	std::vector<FKLegRef> legs;

	glm::vec3 bodyPos;



	
};