#include "MeshData.h"
using namespace ci;
using namespace ci::app;
using namespace std;

MeshDataRef MeshData::create()
{
	MeshDataRef ref = std::make_shared<MeshData>();
	return ref;
}
