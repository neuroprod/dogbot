#pragma once
#include "cinder/app/App.h"
#include "Mesh.h"
class MeshData;
typedef std::shared_ptr<MeshData> MeshDataRef;

class MeshData
{
public:
	MeshData() {};
	

	static MeshDataRef create();
	std::string type;
	std::vector<MeshRef> meshes;
	ci::mat4 globalMatrix;

	
};