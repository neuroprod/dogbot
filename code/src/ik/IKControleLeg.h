#pragma once
#include "cinder/app/App.h"

class IKControleLeg;
typedef std::shared_ptr<IKControleLeg  > IKControleLegRef;

class IKControleLeg
{
public:
	IKControleLeg() {};
	static IKControleLegRef create();

	ci::vec3 homePos;
	ci::vec3 targetPos;


};