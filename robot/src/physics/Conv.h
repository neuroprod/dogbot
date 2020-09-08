#pragma once
#include "glm/glm.hpp"
#include "btBulletDynamicsCommon.h"
class Conv
{


public:
	Conv() {};

	
	 static glm::mat4 to(const btTransform & in);
	 static btTransform to(const glm::mat4 & in);


};