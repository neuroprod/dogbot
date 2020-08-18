#pragma once
#include "cinder/app/App.h"

#include "IKLeg.h"


class IKModel;
typedef std::shared_ptr<IKModel> IKModelRef;

class IKModel 
{
public:
	IKModel() {};
	void setup();
	void update();
	void reBuild();




	std::vector<IKLegRef> legs;


	IKLegRef FR;
	IKLegRef FL;
	IKLegRef BR;
	IKLegRef BL;
};