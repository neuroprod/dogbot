//
// Created by kris on 26.08.20.
//

#ifndef BOT_FLOOR_H
#define BOT_FLOOR_H

#include "glm/glm.hpp"

#include "btBulletDynamicsCommon.h"
#include "Conv.h"


class Floor
{
public:
    Floor(){};
    void setup()
    {
       glm::vec3 mSize = glm::vec3(100, 5, 100);

     colShape= new btBoxShape(btVector3(mSize.x / 2, mSize.y / 2, mSize.z / 2));
        glm::mat4 m;
        m = glm::translate(m, glm::vec3(0, -2.5, 0));

        btTransform startTransform = Conv::to(m);
        btScalar btmass(0);
        btVector3 localInertia(0, 0, 0);


        myMotionState = new btDefaultMotionState(startTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(btmass, myMotionState, colShape, localInertia);
        body= new btRigidBody(rbInfo);
        body->setActivationState(DISABLE_DEACTIVATION);
        body->setFriction(1.f);
        body->setRestitution(0.0f);
      //  m_dynamicsWorld->addRigidBody(body);

    }
   btCollisionShape* colShape = nullptr;
    btDefaultMotionState* myMotionState= nullptr;
    btRigidBody * body= nullptr;
};


#endif //BOT_FLOOR_H
