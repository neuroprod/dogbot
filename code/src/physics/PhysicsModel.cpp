//
// Created by kris on 26.08.20.
//

#include "PhysicsModel.h"
#include "../RobotSettings.h"
#include "Conv.h"

using namespace ci;
void PhysicsModel::updateData()
{
    btTransform tr = mMultiBody->getBaseWorldTransform();


    bodyMatrix = Conv::to(tr);

    vec4 lPos = bodyMatrix * vec4(0, 0, 0, 1);
    bodyPos =vec3( lPos);

    vec4 lPosZ = bodyMatrix * vec4(0, 0,1, 1);
    vec4 lPosX = bodyMatrix * vec4(1, 0, 0, 1);
    vec3 lPosZN = vec3(lPosZ - lPos);
    vec3 lPosXN = vec3(lPosX - lPos);
    angleX = 0;
    angleZ= 0;
    if (lPosZN.y < -0.001f || lPosZN.y > 0.001f) {

        vec3 lPosZF = lPosZN;
        lPosZF.y = 0;;

        angleX = acos(glm::dot(glm::normalize(lPosZN), glm::normalize(lPosZF)));
        if (lPosZN.y > 0) angleX *= -1.f;
    }

    if (lPosXN.y < -0.001f || lPosXN.y > 0.001f) {


        vec3 lPosXF = lPosXN;
        lPosXF.y = 0;;

        angleZ = acos(glm::dot(glm::normalize(lPosXN), glm::normalize(lPosXF)));
        if (lPosXN.y < 0) angleZ *= -1.f;
    }


    int count = 0;
    for (int i = 0; i <16; i++)
    {
        if (i % 4 != 3) {
            angles[count++] = mMultiBody->getJointPos(i);

        }
    }

    for (int i = 0; i < legs.size(); i++)
    {
        legs[i]->updateData();
    }


}
void PhysicsModel::setMotorTargets(std::vector<float> &targets)
{
    float Kp = 1.0f;
    for (int i = 0; i < legs.size(); i++)
    {
        int index = i * 3;
        legs[i]->motorHip1->setPositionTarget(targets[index], Kp);

        legs[i]->motorHip2->setPositionTarget(targets[index + 1], Kp);
        legs[i]->motorKnee->setPositionTarget(targets[index + 2], Kp);

    }

}
void PhysicsModel::setDefaultAngles(std::vector<float>  targets)
{

    defaultAngles = targets;


}
void PhysicsModel::setup(btMultiBodyDynamicsWorld* world)
{
    angles.resize(12);
    int numLinks = 16;


    btVector3 baseHalfExtents(BOTSETTINGS()->bodyLength/ 2000.f, 80.0f / 2000.f, BOTSETTINGS()->bodyWidth / 2000.f);
    BOTSETTINGS()->bodyXStart;;

    btVector3 basePosition = btVector3(BOTSETTINGS()->bodyXStart/1000, BOTSETTINGS()->bodyYStart/1000, 0.f);

    btVector3 baseInertiaDiag(0.f, 0.f, 0.f);
    float baseMass = 6;
    if (baseMass)
    {
        btCollisionShape* shape = new btBoxShape(btVector3(baseHalfExtents[0], baseHalfExtents[1], baseHalfExtents[2]));
        shape->calculateLocalInertia(baseMass, baseInertiaDiag);
        delete shape;
    }
    mMultiBody = new btMultiBody(numLinks, baseMass, baseInertiaDiag, false, false);
    btQuaternion baseOriQuat(0.f, 0.f, 0.f, 1.f);



    mMultiBody->setBasePos(basePosition);
    mMultiBody->setWorldToBaseRot(baseOriQuat);

    FRLeg = PhysicsLeg::create();
    FRLeg->setup("FR", vec3(BOTSETTINGS()->bodyLength / 2, 0, BOTSETTINGS()->bodyWidth / 2),  mMultiBody, 0);
    legs.push_back(FRLeg);

    FLLeg = PhysicsLeg::create();
    FLLeg->setup("FL", vec3(BOTSETTINGS()->bodyLength / 2, 0, -BOTSETTINGS()->bodyWidth / 2),  mMultiBody, 4);
    legs.push_back(FLLeg);

    BRLeg = PhysicsLeg::create();
    BRLeg->setup("BR", vec3(-BOTSETTINGS()->bodyLength / 2, 0, BOTSETTINGS()->bodyWidth / 2),  mMultiBody, 8);
    legs.push_back(BRLeg);

    BLLeg = PhysicsLeg::create();
    BLLeg->setup("BL", vec3(-BOTSETTINGS()->bodyLength / 2, 0, -BOTSETTINGS()->bodyWidth / 2), mMultiBody, 12);
    legs.push_back(BLLeg);
    mMultiBody->finalizeMultiDof();
    world->addMultiBody(mMultiBody);

    mMultiBody->setCanSleep(false);
    mMultiBody->setHasSelfCollision(false);


    mMultiBody->setLinearDamping(0.1f);
    mMultiBody->setAngularDamping(0.9f);

    int collisionFilterGroup = int(btBroadphaseProxy::DefaultFilter);
    int collisionFilterMask = int(btBroadphaseProxy::AllFilter);

    shape = new btBoxShape(btVector3(baseHalfExtents[0], baseHalfExtents[1], baseHalfExtents[2]));
    col = new btMultiBodyLinkCollider(mMultiBody, -1);
    col->setCollisionShape(shape);

    btTransform trw;
    trw.setIdentity();
    trw.setOrigin(basePosition);



    world->addCollisionObject(col, collisionFilterGroup, collisionFilterMask);  //, 2,1+2);
    mMultiBody->setBaseCollider(col);

    btAlignedObjectArray<btQuaternion> world_to_local;
    world_to_local.resize(mMultiBody->getNumLinks() + 1);

    btAlignedObjectArray<btVector3> local_origin;
    local_origin.resize(mMultiBody->getNumLinks() + 1);
    world_to_local[0] = mMultiBody->getWorldToBaseRot();
    local_origin[0] = mMultiBody->getBasePos();

    for (int i = 0; i < mMultiBody->getNumLinks(); ++i)
    {
        const int parent = mMultiBody->getParent(i);
        world_to_local[i + 1] = mMultiBody->getParentToLocalRot(i) * world_to_local[parent + 1];
        local_origin[i + 1] = local_origin[parent + 1] + (quatRotate(world_to_local[i + 1].inverse(), mMultiBody->getRVector(i)));
    }

    for (int i = 0; i < mMultiBody->getNumLinks(); ++i)
    {
        btVector3 posr = local_origin[i + 1];
        //	float pos[4]={posr.x(),posr.y(),posr.z(),1};

        btScalar quat[4] = { -world_to_local[i + 1].x(), -world_to_local[i + 1].y(), -world_to_local[i + 1].z(), world_to_local[i + 1].w() };
        btCollisionShape* shape = new btSphereShape(BOTSETTINGS()->footRadius / 1000.f);

        btMultiBodyLinkCollider* col = new btMultiBodyLinkCollider(mMultiBody, i);
        col->setFriction(1.0);
        col->setRestitution(0.0f);
        col->setCollisionShape(shape);

        btTransform tr;
        tr.setIdentity();
        tr.setOrigin(posr);
        tr.setRotation(btQuaternion(quat[0], quat[1], quat[2], quat[3]));
        linkColiders.push_back(col);

        world->addCollisionObject(col, btBroadphaseProxy::DefaultFilter, btBroadphaseProxy::AllFilter);


        mMultiBody->getLink(i).m_collider = col;


    }
    float mTor = 1.000f;

    FRLeg->motorHip1 = new btMultiBodyJointMotor(mMultiBody, 0, 0, mTor);
    FRLeg->motorHip2 = new btMultiBodyJointMotor(mMultiBody, 1, 0, mTor);
    FRLeg->motorKnee = new btMultiBodyJointMotor(mMultiBody, 2, 0.0, mTor);

    FLLeg->motorHip1 = new btMultiBodyJointMotor(mMultiBody, 4, 0, mTor);
    FLLeg->motorHip2 = new btMultiBodyJointMotor(mMultiBody, 5, 0, mTor);
    FLLeg->motorKnee = new btMultiBodyJointMotor(mMultiBody, 6, 0, mTor);

    BRLeg->motorHip1 = new btMultiBodyJointMotor(mMultiBody, 8, 0, mTor);
    BRLeg->motorHip2 = new btMultiBodyJointMotor(mMultiBody, 9, 0, mTor);
    BRLeg->motorKnee = new btMultiBodyJointMotor(mMultiBody, 10, 0, mTor);

    BLLeg->motorHip1 = new btMultiBodyJointMotor(mMultiBody, 12, 0, mTor);
    BLLeg->motorHip2 = new btMultiBodyJointMotor(mMultiBody, 13, 0, mTor);
    BLLeg->motorKnee = new btMultiBodyJointMotor(mMultiBody, 14, 0, mTor);

    world->addMultiBodyConstraint(FRLeg->motorHip1);
    world->addMultiBodyConstraint(FRLeg->motorHip2);
    world->addMultiBodyConstraint(FRLeg->motorKnee);

    world->addMultiBodyConstraint(FLLeg->motorHip1);
    world->addMultiBodyConstraint(FLLeg->motorHip2);
    world->addMultiBodyConstraint(FLLeg->motorKnee);

    world->addMultiBodyConstraint(BRLeg->motorHip1);
    world->addMultiBodyConstraint(BRLeg->motorHip2);
    world->addMultiBodyConstraint(BRLeg->motorKnee);

    world->addMultiBodyConstraint(BLLeg->motorHip1);
    world->addMultiBodyConstraint(BLLeg->motorHip2);
    world->addMultiBodyConstraint(BLLeg->motorKnee);


    motors.push_back(FRLeg->motorHip1);
    motors.push_back(FRLeg->motorHip2);
    motors.push_back(FRLeg->motorKnee);

    motors.push_back(FLLeg->motorHip1);
    motors.push_back(FLLeg->motorHip2);
    motors.push_back(FLLeg->motorKnee);

    motors.push_back(BRLeg->motorHip1);
    motors.push_back(BRLeg->motorHip2);
    motors.push_back(BRLeg->motorKnee);

    motors.push_back(BLLeg->motorHip1);
    motors.push_back(BLLeg->motorHip2);
    motors.push_back(BLLeg->motorKnee);


    for (int i = 0; i < 4; i++)
    {

        mMultiBody->setJointPos(i * 4, defaultAngles[ i*3]);

        mMultiBody->setJointPos(i * 4 + 1, defaultAngles[i * 3+1]);
        mMultiBody->setJointPos(i * 4 + 2, defaultAngles[i * 3+2]);
        mMultiBody->setJointVel(i * 4, 0.f);
        mMultiBody->setJointVel(i * 4+1, 0.f);
        mMultiBody->setJointVel(i * 4+2, 0.f);
    }

}

void PhysicsModel::clean(btMultiBodyDynamicsWorld* world)
{




    world->removeMultiBody(mMultiBody);
    for(auto coll:linkColiders)
    {

        world->removeCollisionObject(coll);
        delete coll;
    }
    world->removeCollisionObject(col);  //, 2,1+2);
    delete col;
    delete shape;

    world->removeMultiBodyConstraint(FRLeg->motorHip1);
    world->removeMultiBodyConstraint(FRLeg->motorHip2);
    world->removeMultiBodyConstraint(FRLeg->motorKnee);

    world->removeMultiBodyConstraint(FLLeg->motorHip1);
    world->removeMultiBodyConstraint(FLLeg->motorHip2);
    world->removeMultiBodyConstraint(FLLeg->motorKnee);

    world->removeMultiBodyConstraint(BRLeg->motorHip1);
    world->removeMultiBodyConstraint(BRLeg->motorHip2);
    world->removeMultiBodyConstraint(BRLeg->motorKnee);

    world->removeMultiBodyConstraint(BLLeg->motorHip1);
    world->removeMultiBodyConstraint(BLLeg->motorHip2);
    world->removeMultiBodyConstraint(BLLeg->motorKnee);

    BLLeg->clean();
    BRLeg->clean();
    FLLeg->clean();
    FRLeg->clean();

    delete mMultiBody;

    motors.clear();
    legs.clear();
    linkColiders.clear();

}
