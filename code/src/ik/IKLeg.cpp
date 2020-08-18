#include "IKLeg.h"
#include "../RobotSettings.h"
using namespace ci;
using namespace ci::app;
using namespace std;


IKLegRef IKLeg::create() 
{
	return make_shared<IKLeg>();
}
void IKLeg::setupPos(ci::vec3 pos)
{
    PI = glm::pi<float>();

    hipOffsetZFlip = 1;
    if (pos.x < 0 && pos.z>0)hipOffsetZFlip = -1;
    if (pos.x > 0 && pos.z<0)hipOffsetZFlip = -1;

    float hip1Rot = 0;
    if (pos.x < 0)hip1Rot = PI;
    hip1Matrix = getBase(pos,  vec3(0,hip1Rot,0));
    hip2Matrix= getBase(vec3(BOTSETTINGS()->hipOffsetX,0 , BOTSETTINGS()->hipOffsetZ*hipOffsetZFlip),vec3(0, -PI/2* hipOffsetZFlip,0));
    build();
}

mat4 IKLeg::getBase(vec3 position, vec3 rotation)
{
    glm::mat4 baseMatrix = glm::mat4();
    baseMatrix = glm::translate(baseMatrix, position);


    baseMatrix = glm::rotate(baseMatrix, rotation.x, vec3(1, 0, 0));
    baseMatrix = glm::rotate(baseMatrix, rotation.y, vec3(0, 1, 0));
    baseMatrix = glm::rotate(baseMatrix, rotation.z, vec3(0, 0, 1));
    return baseMatrix;

}
void IKLeg::setup(mat4 _hip1Matrix, mat4 _hip2Matrix)
{


	
	hip1Matrix = _hip1Matrix;
	hip2Matrix = _hip2Matrix;



	build();
}
void IKLeg::build(){


	invHip1Matrix = glm::inverse(hip1Matrix);
	
	invHip2Matrix = glm::inverse(hip2Matrix);

}
void IKLeg::resolve(glm::vec3 target, glm::mat4 invBodyMatrix) 
{

	targetHip1Local = invHip1Matrix* invBodyMatrix *vec4(target.x,target.y,target.z,1.f) ;
	
	targetHip1LocalFlat = vec3(0, targetHip1Local.y, targetHip1Local.z);
	//pythagoras theorem C2= A2+B2
	float C = glm::length(targetHip1LocalFlat);
	float B = BOTSETTINGS()->hipOffsetZ ;
	float A = sqrtf(C*C - B*B);
;
	float angleCX = atan2f(targetHip1LocalFlat.y, targetHip1LocalFlat.z);

	//sine law
	float angleBC = asinf(A / (C / sinf(PI / 2)));
	if (hipOffsetZFlip==1) 
	{
		angleHip1 = (angleCX + angleBC)*-1;
	}
	else 
	{
		angleHip1 =  (angleCX - angleBC)*-1+PI;
	}

	mat4 hip1MatrixRot = glm::rotate(hip1Matrix, angleHip1, vec3(1, 0, 0));
	mat4 invHip1MatrixRot = glm::inverse(hip1MatrixRot);


	targetHip2Local = invHip2Matrix* invHip1MatrixRot *invBodyMatrix *vec4(target.x, target.y, target.z, 1.f);





		
	//resolve in XY;
	
	vec2 targetHip1LocalFlat = vec2(targetHip2Local.z, targetHip2Local.y);

	
	C = glm::length(targetHip1LocalFlat);
	A = BOTSETTINGS()->upperLegLength;
	B =  BOTSETTINGS()->underLegLength-  BOTSETTINGS()->footRadius;

	
	if (isLeft) {
		angleCX = atan2f(targetHip1LocalFlat.y, targetHip1LocalFlat.x);

		//cos law 
		//b = aCos((C2 + A2 - B2) / − 2AC)
		float angleB = acosf((C*C + A*A - B*B) / (2.f * A*C));
		angleHip2 = (angleCX - angleB)*-1 - PI / 2;
		angleKnee = (acosf((A*A + B*B - C*C) / (2.f * A*B)))+PI ;

	}
	else 
	{
		angleCX = atan2f(targetHip1LocalFlat.y, targetHip1LocalFlat.x)*-1;

		//cos law 
		//b = aCos((C2 + A2 - B2) / − 2AC)
		float angleB = acosf((C*C + A*A - B*B) / (2.f * A*C));
		angleHip2 = angleCX - angleB - PI / 2;
		angleKnee = (acosf((A*A + B*B - C*C) / (2.f * A*B)))*-1 + PI;
	}
	
	
}