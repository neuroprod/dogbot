//
// Created by kris on 22.08.20.
//

#include "PhysicsWorld.h"
#include "Conv.h"
using namespace ci;
using namespace ci::app;
using namespace std;

void PhysicsWorld::setup() {

    m_collisionConfiguration = new btDefaultCollisionConfiguration();
    m_filterCallback = new MyOverlapFilterCallback2();
    m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
    m_pairCache = new btHashedOverlappingPairCache();
    m_pairCache->setOverlapFilterCallback(m_filterCallback);
    m_broadphase = new btDbvtBroadphase(m_pairCache);
    m_solver = new btMultiBodyConstraintSolver;

    m_dynamicsWorld = new btMultiBodyDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
    m_dynamicsWorld->setGravity(btVector3(0, -10.f, 0));
    m_dynamicsWorld->getSolverInfo().m_jointFeedbackInWorldSpace = true;
    m_dynamicsWorld->getSolverInfo().m_jointFeedbackInJointFrame = true;



}
void PhysicsWorld::update()
{
    m_dynamicsWorld->stepSimulation(1. / 120, 5,1.f/480);

   // m_dynamicsWorld->stepSimulation(1. / 240, 0);

};

void PhysicsWorld::clear() {

   /* delete m_dynamicsWorld;
    delete m_solver;
    delete m_broadphase;
    delete m_pairCache;
    delete m_dispatcher;
    delete m_filterCallback;
    delete m_collisionConfiguration;*/
}