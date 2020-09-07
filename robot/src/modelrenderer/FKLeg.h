#pragma once
#include "cinder/app/App.h"
#include "FKNode.h"



class FKLeg;
typedef std::shared_ptr<FKLeg> FKLegRef;

class FKLeg
{

public:

	FKLeg() {};
	static FKLegRef create();
	void setup(std::string name,FKNodeRef body,glm::vec3 pos, std::vector<FKNodeRef> &nodes);



	float hipOffsetZFlip;
	FKNodeRef hip;
	FKNodeRef knee ;
	FKNodeRef ankle;
    FKNodeRef toe;
};