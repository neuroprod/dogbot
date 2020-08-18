#include "FKNode.h"
#include "cinder/gl/gl.h"
#include "MeshDataPool.h"
using namespace ci;
using namespace ci::app;
using namespace std;

FKNode::FKNode(string _name,string _type)
{
	name = _name;
	type = _type;
	meshData = MDP()->getMesh(_type);
}

FKNodeRef FKNode::create(string name, string type)
{
	FKNodeRef ref = std::make_shared<FKNode>(name,type);

	return ref;
}

void FKNode::addChild(FKNodeRef ref)
{
	ref->parent = shared_from_this();
	children.push_back(ref);


}
void  FKNode::removeAllChildren()
{
	for (auto child : children)
	{
		child->removeAllChildren();
	}
	children.clear();
}

void FKNode::setBase(vec3 position)
{
	baseMatrix = glm::mat4();
	baseMatrix = glm::translate(baseMatrix, position);



}
void FKNode::setBase(vec3 position, vec3 rotation)
{
	baseMatrix = glm::mat4();
	baseMatrix = glm::translate(baseMatrix, position);


	baseMatrix = glm::rotate(baseMatrix, rotation.x, vec3(1, 0, 0));
	baseMatrix = glm::rotate(baseMatrix, rotation.y, vec3(0, 1, 0));
	baseMatrix = glm::rotate(baseMatrix, rotation.z, vec3(0, 0, 1));

}

void FKNode::setRotation(float r)
{
	currentRotation = r;
	
}
void FKNode::update()
{

	localMatrix = baseMatrix;

	localMatrix = glm::rotate(localMatrix, currentRotation, vec3(1, 0, 0));
	if (parent)
	{
		globalMatrix = parent->globalMatrix *localMatrix;
		
	}
	else
	{
		globalMatrix = localMatrix;
		
	}

	for (auto child : children)
	{
		child->update();
	}

}

