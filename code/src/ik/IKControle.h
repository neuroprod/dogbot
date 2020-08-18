#pragma once
#include "cinder/app/App.h"

#include "IKControleLeg.h"
#include "IKModel.h"
class IKControle;
typedef std::shared_ptr<IKControle  > IKControleRef;

class IKControle
{
public:
    IKControle() {};
	void setup();
	void setBase();
    void update();
	void drawGui();

    IKModel model;

	float bodyX = 50;
	float bodyY = 0;
	float bodyZ = 0;

	float bodyRotX = 0;
	float bodyRotY = 0;
	float bodyRotZ = 0;

	IKControleLegRef FR;
	IKControleLegRef FL;
	IKControleLegRef BR;
	IKControleLegRef BL;

	std::vector<IKControleLegRef> legs;


    glm::mat4 bodyMatrix;
    std::vector<float> angles;
};