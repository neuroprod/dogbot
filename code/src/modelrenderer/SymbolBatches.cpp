#include "SymbolBatches.h"
#include "MeshDataPool.h"
using namespace ci;
using namespace ci::app;
using namespace std;

void SymbolBatches::setup()
{
	makeFloor();
	makeHome();
	makeTarget();
	makeCoordinateFrame();
	makeCOF();
}

void SymbolBatches::makeFloor()
{
	
	floorBatch = gl::Batch::create(geom::Plane().size(vec2(100000, 100000)), MDP()->mGlsl);
}
void SymbolBatches::makeCOF() 
{
COFBatch= gl::Batch::create(geom::WireCube().size(20,20,20), gl::getStockShader(gl::ShaderDef().color()));

}

void SymbolBatches::makeCoordinateFrame() 
{
	struct VertexData {
		vec3 position;
		vec3 color;
	};

	float size = 40;

	auto vertices = vector<VertexData>();

	{
		VertexData v1;
		v1.position = vec3(0, 0, 0);
		v1.color = vec3(1, 0, 0);
		vertices.push_back(v1);

		VertexData v2;
		v2.position = vec3(size, 0, 0);
		v2.color = vec3(1,0, 0);
		vertices.push_back(v2);
	}

	{
		VertexData v1;
		v1.position = vec3(0, 0, 0);
		v1.color = vec3(0, 1, 0);
		vertices.push_back(v1);

		VertexData v2;
		v2.position = vec3(0, size, 0);
		v2.color = vec3(0, 1, 0);
		vertices.push_back(v2);
	}

	{
		VertexData v1;
		v1.position = vec3(0, 0, 0);
		v1.color = vec3(0, 0, 1);
		vertices.push_back(v1);

		VertexData v2;
		v2.position = vec3(0, 0, size);
		v2.color = vec3(0, 0, 1);
		vertices.push_back(v2);
	}

	auto layout = geom::BufferLayout();
	layout.append(geom::Attrib::POSITION, 3, sizeof(VertexData), offsetof(VertexData, position));
	layout.append(geom::Attrib::COLOR, 3, sizeof(VertexData), offsetof(VertexData, color));

	auto buffer = gl::Vbo::create(GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW);


	auto mesh = gl::VboMesh::create(vertices.size(), GL_LINES, { { layout, buffer } });

	coordinateFrame = gl::Batch::create(mesh, gl::getStockShader(gl::ShaderDef().color()));

}
void SymbolBatches::makeTarget() 
{
	struct VertexData {
		vec3 position;
		vec3 color;
	};

	float size = 40;

	auto vertices = vector<VertexData>();
	{
		VertexData v1;
		v1.position = vec3(-size, 0, 0);
		v1.color = vec3(1, 1, 1);
		vertices.push_back(v1);

		VertexData v2;
		v2.position = vec3(size, 0,0);
		v2.color = vec3(1, 1, 1);
		vertices.push_back(v2);
	}
	{
		VertexData v1;
		v1.position = vec3(0, 0, -size);
		v1.color = vec3(1, 1, 1);
		vertices.push_back(v1);

		VertexData v2;
		v2.position = vec3(0, 0, size);
		v2.color = vec3(1, 1, 1);
		vertices.push_back(v2);
	}
	{
		VertexData v1;
		v1.position = vec3(0, -size,0);
		v1.color = vec3(1, 1, 1);
		vertices.push_back(v1);

		VertexData v2;
		v2.position = vec3(0, size, 0);
		v2.color = vec3(1, 1, 1);
		vertices.push_back(v2);
	}
	auto layout = geom::BufferLayout();
	layout.append(geom::Attrib::POSITION, 3, sizeof(VertexData), offsetof(VertexData, position));
	layout.append(geom::Attrib::COLOR, 3, sizeof(VertexData), offsetof(VertexData, color));

	auto buffer = gl::Vbo::create(GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW);


	auto mesh = gl::VboMesh::create(vertices.size(), GL_LINES, { { layout, buffer } });

	targetBatch = gl::Batch::create(mesh, gl::getStockShader(gl::ShaderDef().color()));

}
void SymbolBatches::makeHome()
{
	struct VertexData {
		vec3 position;
		vec3 color;
	};

	float size = 40;

	auto vertices = vector<VertexData>();
	{
		VertexData v1;
		v1.position = vec3(-size, 0, size);
		v1.color = vec3(1, 1, 1);
		vertices.push_back(v1);

		VertexData v2;
		v2.position = vec3(size, 0, -size);
		v2.color = vec3(1, 1, 1);
		vertices.push_back(v2);
	}
	{
		VertexData v1;
		v1.position = vec3(-size, 0, -size);
		v1.color = vec3(1, 1, 1);
		vertices.push_back(v1);

		VertexData v2;
		v2.position = vec3(size, 0, size);
		v2.color = vec3(1, 1, 1);
		vertices.push_back(v2);
	}

	auto layout = geom::BufferLayout();
	layout.append(geom::Attrib::POSITION, 3, sizeof(VertexData), offsetof(VertexData, position));
	layout.append(geom::Attrib::COLOR, 3, sizeof(VertexData), offsetof(VertexData, color));

	auto buffer = gl::Vbo::create(GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW);


	auto mesh = gl::VboMesh::create(vertices.size(), GL_LINES, { { layout, buffer } });

	homeBatch = gl::Batch::create(mesh, gl::getStockShader(gl::ShaderDef().color()));
}