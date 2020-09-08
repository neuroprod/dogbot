#pragma once
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/TriMesh.h"
#include "Material.h"
class Mesh;
typedef std::shared_ptr<Mesh> MeshRef;

class Mesh 
{
public:
	static MeshRef create();
	Mesh() {};
	void setup( const ci::geom::Source &source,  Material mat, ci::gl::GlslProgRef mGlsl,ci::vec3 pos =ci::vec3(0),ci::vec3 rot =ci::vec3(0),ci::vec3 scale =ci::vec3(1,1,1));
    void setup( cinder::TriMeshRef meshRef,  Material mat, ci::gl::GlslProgRef mGlsl,ci::vec3 pos=ci::vec3(0),ci::vec3 rot =ci::vec3(0),ci::vec3 scale =ci::vec3(1,1,1));
	void draw();
	void drawShadow();

	std::string mName;
    Material mMat;
	ci::gl::BatchRef mainBatch;
	ci::gl::BatchRef shadowedBatch;

    ci::mat4 modelMatrix;
};