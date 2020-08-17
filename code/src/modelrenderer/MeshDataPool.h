#pragma once
#include "../utils/Singleton.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

#include "MeshData.h"
#include "cinder/TriMesh.h"

class MeshDataPool
{

public:
	MeshDataPool();
	void setup();
	MeshDataRef getMesh(std::string type);

	ci::gl::GlslProgRef mGlsl;

    cinder::TriMeshRef ankle;

};

typedef Singleton<MeshDataPool > NodeDataPoolSingleton;

inline MeshDataPool * MDP() {
	return  NodeDataPoolSingleton::Instance();
}
