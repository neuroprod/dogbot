//
// Created by kris on 26.08.20.
//

#ifndef BOT_PHYSICSMODEL_H
#define BOT_PHYSICSMODEL_H

#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Featherstone/btMultiBodyDynamicsWorld.h"
#include "BulletDynamics/Featherstone/btMultiBodyConstraintSolver.h"
#include "BulletDynamics/Featherstone/btMultiBodyPoint2Point.h"
#include "BulletDynamics/Featherstone/btMultiBodyLinkCollider.h"
#include "BulletDynamics/Featherstone/btMultiBodyJointMotor.h"
#include "BulletDynamics/Featherstone/btMultiBodyJointFeedback.h"
#include "PhysicsLeg.h"

class PhysicsModel
{
public:
    PhysicsModel(){}
    void setup(  btMultiBodyDynamicsWorld* world);
    void setDefaultAngles(std::vector<float>  defaultAngles);
    void setMotorTargets(std::vector<float> &targets);
    void clean(btMultiBodyDynamicsWorld* world);
    void updateData();
    PhysicsLegRef FRLeg;
    PhysicsLegRef FLLeg;
    PhysicsLegRef BRLeg;
    PhysicsLegRef BLLeg;
    std::vector<PhysicsLegRef> legs;

    btMultiBody* mMultiBody =nullptr;

    btCollisionShape* shape ;
    btMultiBodyLinkCollider* col;

    std::vector<btMultiBodyLinkCollider*> linkColiders;
    std::vector< btMultiBodyJointMotor*>motors;

    glm::mat4 bodyMatrix;
    std::vector<float> angles;
    std::vector<ci::vec3> positions;
    std::vector<float>  defaultAngles;
    ci::vec3 bodyPos;
    float angleX =0;
    float angleZ=0;
};


#endif //BOT_PHYSICSMODEL_H
