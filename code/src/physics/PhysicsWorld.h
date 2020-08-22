//
// Created by kris on 22.08.20.
//

#ifndef BOT_PHYSICSWORLD_H
#define BOT_PHYSICSWORLD_H
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Featherstone/btMultiBodyDynamicsWorld.h"
#include "BulletDynamics/Featherstone/btMultiBodyConstraintSolver.h"
#include "BulletDynamics/Featherstone/btMultiBodyPoint2Point.h"
#include "BulletDynamics/Featherstone/btMultiBodyLinkCollider.h"
#include "BulletDynamics/Featherstone/btMultiBodyJointMotor.h"
#include "BulletDynamics/Featherstone/btMultiBodyJointFeedback.h"
enum MyFilterModes
{
    FILTER_GROUPAMASKB_AND_GROUPBMASKA2 = 0,
    FILTER_GROUPAMASKB_OR_GROUPBMASKA2
};

struct MyOverlapFilterCallback2 : public btOverlapFilterCallback
{
    int m_filterMode;

    MyOverlapFilterCallback2()
            : m_filterMode(FILTER_GROUPAMASKB_AND_GROUPBMASKA2)
    {
    }

    virtual ~MyOverlapFilterCallback2()
    {
    }
    // return true when pairs need collision
    virtual bool needBroadphaseCollision(btBroadphaseProxy* proxy0, btBroadphaseProxy* proxy1) const
    {
        if (m_filterMode == FILTER_GROUPAMASKB_AND_GROUPBMASKA2)
        {
            bool collides = (proxy0->m_collisionFilterGroup & proxy1->m_collisionFilterMask) != 0;
            collides = collides && (proxy1->m_collisionFilterGroup & proxy0->m_collisionFilterMask);
            return collides;
        }

        if (m_filterMode == FILTER_GROUPAMASKB_OR_GROUPBMASKA2)
        {
            bool collides = (proxy0->m_collisionFilterGroup & proxy1->m_collisionFilterMask) != 0;
            collides = collides || (proxy1->m_collisionFilterGroup & proxy0->m_collisionFilterMask);
            return collides;
        }
        return false;
    }
};


class PhysicsWorld
{
public:
    PhysicsWorld(){};
    void setup(){};
    btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
    MyOverlapFilterCallback2* m_filterCallback;
    btOverlappingPairCache* m_pairCache;
    btBroadphaseInterface* m_broadphase;
    btCollisionDispatcher* m_dispatcher;
    btMultiBodyConstraintSolver* m_solver;
    btDefaultCollisionConfiguration* m_collisionConfiguration;
    btMultiBodyDynamicsWorld* m_dynamicsWorld;
};


#endif //BOT_PHYSICSWORLD_H
