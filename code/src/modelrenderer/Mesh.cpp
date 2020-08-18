
#include "Mesh.h"

using namespace ci;
using namespace ci::app;
using namespace std;

MeshRef Mesh::create()
{
	MeshRef ref = std::make_shared<Mesh>();
	return ref;
}


void Mesh::setup(const ci::geom::Source &source,  Material mat, ci::gl::GlslProgRef mGlsl, ci::vec3 pos, ci::vec3 rot,ci::vec3 scale)
{

    modelMatrix = glm::translate(modelMatrix,pos);
    glm::mat4 rotationM = glm::eulerAngleXYZ(rot.x, rot.y, rot.z);
    modelMatrix =modelMatrix*rotationM;

    mMat =mat;
	mainBatch= gl::Batch::create(source, mGlsl);
	shadowedBatch = gl::Batch::create(source, gl::getStockShader(gl::ShaderDef()));

}
void Mesh::setup(TriMeshRef mMesh,    Material mat, ci::gl::GlslProgRef mGlsl, ci::vec3 pos, ci::vec3 rot,ci::vec3 scale)
{

    modelMatrix =glm::translate(modelMatrix,pos);
    glm::mat4 rotationM = glm::eulerAngleXYZ(rot.x, rot.y, rot.z);
    modelMatrix =modelMatrix*rotationM;

    mMat =mat;

    mainBatch= gl::Batch::create( *mMesh, mGlsl);
    shadowedBatch = gl::Batch::create( *mMesh, gl::getStockShader(gl::ShaderDef()));

}
void Mesh::draw() 
{

	gl::color(mMat.color);
    mainBatch->getGlslProg()->uniform("spec",mMat.spec );

	mainBatch->draw();

}
void Mesh::drawShadow() 
{

	shadowedBatch->draw();

}

