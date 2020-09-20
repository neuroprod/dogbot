#pragma once
#include "cinder/app/App.h"

#include "IKControleLeg.h"
#include "IKModel.h"
class IKController;
typedef std::shared_ptr<IKController  > IKControleRef;

class IKController
{
public:
    IKController() {};
	void setup();
	void setBase();
    void update();
	void drawGui();
    void reset();
    void setBalance(float offsetX,float offsetZ);
    float clampAngle(float);

    IKModel model;

    float mOffsetX =0;
    float mOffsetZ=0;
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
    float PI = 3.14159265359;

    glm::mat4 bodyMatrix;
    std::vector<float> angles;


};