#include "PhysicsLeg.h"
#include "../RobotSettings.h"
using namespace ci;
using namespace ci::app;
using namespace std;
PhysicsLegRef PhysicsLeg::create()
{
	PhysicsLegRef ref = std::make_shared<PhysicsLeg>();
	return ref;
}
void PhysicsLeg::updateData() 
{
	tHip1 = motorHip1->getAppliedImpulse(0) * 120;
	tHip2 = motorHip2->getAppliedImpulse(0) * 120;
	tKnee = motorKnee->getAppliedImpulse(0) * 120;
	
	torque.x = tHip1;
	torque.y = tHip2;
	torque.z = tKnee;
}
void PhysicsLeg::setup(std::string name, glm::vec3 pos, btMultiBody* multiBody, int linkIndex)
{

	float  PI = glm::pi<float>();

	float hipOffsetZFlip = 1;
	if (pos.x < 0 && pos.z>0)hipOffsetZFlip = -1;
	if (pos.x > 0 && pos.z < 0)hipOffsetZFlip = -1;

	float hip1Rot = 0;
	if (pos.x < 0)hip1Rot = PI;

	//hip

	{
		btVector3 linkInertiaDiag(0.f, 0.f, 0.f);
		btCollisionShape* shape = 0;
		btVector3 linkHalfExtents(0.05, 0.05, 0.05);
		float linkMass = BOTSETTINGS()->hipMass;
		shape = new btBoxShape(btVector3(linkHalfExtents[0], linkHalfExtents[1], linkHalfExtents[2]));  //
		shape->calculateLocalInertia(BOTSETTINGS()->hipMass, linkInertiaDiag);
		delete shape;

		glm::quat c;
		c = glm::rotate(c, hip1Rot, vec3(0, 1, 0));
		btVector3 hingeJointAxis(1, 0, 0);
		btVector3 parentComToCurrentPivot(pos.x / 1000.f, pos.y / 1000.f, pos.z / 1000.f);
		vec3 com = BOTSETTINGS()->hipCOM;
		btVector3 currentPivotToCurrentCom(com.x / 1000.f, com.y / 1000.f, com.z / 1000.f);


		multiBody->setupRevolute(linkIndex, linkMass, linkInertiaDiag, -1,
			btQuaternion(c.x, c.y, c.z, c.w),
			hingeJointAxis,
			parentComToCurrentPivot,
			currentPivotToCurrentCom, false);
	}
	//knee

	{
		btVector3 linkInertiaDiag(0.f, 0.f, 0.f);
		btCollisionShape* shape = 0;
		btVector3 linkHalfExtents(0.05, 0.05, 0.05);
		float linkMass = BOTSETTINGS()->kneeMass;
		shape = new btBoxShape(btVector3(linkHalfExtents[0], linkHalfExtents[1], linkHalfExtents[2]));  //
		shape->calculateLocalInertia(BOTSETTINGS()->kneeMass, linkInertiaDiag);
		delete shape;

		glm::quat c;
		c = glm::rotate(c, -PI / 2 * hipOffsetZFlip, vec3(0, 1, 0));
		btVector3 hingeJointAxis(-1, 0, 0);
		vec3 com1 =BOTSETTINGS()->hipCOM;
		vec3 comAdj = (vec3(BOTSETTINGS()->hipOffsetX, 0, BOTSETTINGS()->hipOffsetZ * hipOffsetZFlip) - com1);

		btVector3 parentComToCurrentPivot(comAdj.x / 1000.f, comAdj.y / 1000.f, comAdj.z / 1000.f);

		vec3 com2 = BOTSETTINGS()->kneeCOM;
		btVector3 currentPivotToCurrentCom(com2.x / 1000.f, com2.y / 1000.f, com2.z / 1000.f);


		multiBody->setupRevolute(linkIndex + 1, linkMass, linkInertiaDiag, linkIndex,
			btQuaternion(c.x, c.y, c.z, c.w),
			hingeJointAxis,
			parentComToCurrentPivot,
			currentPivotToCurrentCom, false);
	}


	//ankle
	{
		btVector3 linkInertiaDiag(0.f, 0.f, 0.f);
		btCollisionShape* shape = 0;
		btVector3 linkHalfExtents(0.05, 0.05, 0.05);
		float linkMass = BOTSETTINGS()->ankleMass;
		shape = new btBoxShape(btVector3(linkHalfExtents[0], linkHalfExtents[1], linkHalfExtents[2]));  //
		shape->calculateLocalInertia(linkMass, linkInertiaDiag);
		delete shape;

		glm::quat c;
		//c = glm::rotate(c, -PI / 2 * hipOffsetZFlip, vec3(0, 1, 0));
		btVector3 hingeJointAxis(-1, 0, 0);
		vec3 com1 = BOTSETTINGS()->kneeCOM;;

		com1.y = (BOTSETTINGS()->upperLegLength + com1.y) * -1;


		btVector3 parentComToCurrentPivot(com1.x / 1000.f, com1.y / 1000.f, com1.z / 1000.f);

		vec3 com2 = BOTSETTINGS()->ankleCOM;
		btVector3 currentPivotToCurrentCom(com2.x / 1000.f, com2.y / 1000.f, com2.z / 1000.f);


		multiBody->setupRevolute(linkIndex + 2, linkMass, linkInertiaDiag, linkIndex + 1,
			btQuaternion(c.x, c.y, c.z, c.w),
			hingeJointAxis,
			parentComToCurrentPivot,
			currentPivotToCurrentCom, false);
	}
	///teo
	{
		btVector3 linkInertiaDiag(0.f, 0.f, 0.f);
		btCollisionShape* shape = 0;
		btVector3 linkHalfExtents(0.05, 0.05, 0.05);
		float linkMass = BOTSETTINGS()->toeMass;
		shape = new btBoxShape(btVector3(linkHalfExtents[0], linkHalfExtents[1], linkHalfExtents[2]));  //
		shape->calculateLocalInertia(BOTSETTINGS()->toeMass, linkInertiaDiag);
		delete shape;

		glm::quat c;

		vec3 com1 = vec3();

		com1.y = (BOTSETTINGS()->underLegLength + BOTSETTINGS()->ankleCOM.y - BOTSETTINGS()->footRadius) * -1;


		btVector3 parentComToCurrentPivot(com1.x / 1000.f, com1.y / 1000.f, com1.z / 1000.f);

		vec3 com2 = BOTSETTINGS()->toeCOM;
		btVector3 currentPivotToCurrentCom(0, 0, 0);


		multiBody->setupFixed(linkIndex + 3, linkMass, linkInertiaDiag, linkIndex + 2,
			btQuaternion(c.x, c.y, c.z, c.w),
			parentComToCurrentPivot,
			currentPivotToCurrentCom, false);
	}

	
	////////////////////////////////////////////






}

void PhysicsLeg::clean()
{
    delete motorHip1;
    btMultiBodyJointMotor* motorHip2;
    btMultiBodyJointMotor* motorKnee;


}