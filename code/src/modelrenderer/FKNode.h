#pragma once
#include "cinder/app/App.h"
#include "MeshData.h"

class FKNode;
typedef std::shared_ptr<FKNode> FKNodeRef;

class FKNode : public std::enable_shared_from_this<FKNode>
{
public:

	FKNode(std::string name, std::string type);
	static FKNodeRef create(std::string name, std::string type);
	
	void addChild(FKNodeRef ref);
	void removeAllChildren();
	void setBase(glm::vec3 position);
	void setBase(glm::vec3 position, glm::vec3 rotation);
	void setRotation(float r);

	void update();
	
	

	MeshDataRef meshData;

	std::string name;
	std::string type;
	FKNodeRef parent = nullptr;
	std::vector<FKNodeRef> children;

	float currentRotation = 0;
	ci::mat4 baseMatrix;
	ci::mat4 localMatrix;
	ci::mat4 globalMatrix;
	//ci::mat4 globalMatrixB;
};