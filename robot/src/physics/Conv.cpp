#include "Conv.h"

 glm::mat4 Conv::to(const btTransform & in) 
{
	btScalar matrix[16];
	in.getOpenGLMatrix(&matrix[0]);

	glm::mat4 m = glm::mat4(matrix[0], matrix[1], matrix[2], matrix[3], matrix[4], matrix[5], matrix[6], matrix[7], matrix[8], matrix[9], matrix[10], matrix[11], matrix[12] * 1000.f, matrix[13] * 1000.f, matrix[14]*1000.f, matrix[15]);
	return m;

}
 btTransform Conv::to(const glm::mat4 & in)
{
	//glm::mat4 inT = glm::transpose(in);
	btScalar matrix[16];
	matrix[0] = in[0][0];
	matrix[1] = in[0][1];
	matrix[2] = in[0][2];
	matrix[3] = in[0][3];

	matrix[4] = in[1][0];
	matrix[5] = in[1][1];
	matrix[6] = in[1][2];
	matrix[7] = in[1][3];

	matrix[8] = in[2][0];
	matrix[9] = in[2][1];
	matrix[10] = in[2][2];
	matrix[11] = in[2][3];

	matrix[12] = in[3][0];
	matrix[13] = in[3][1];
	matrix[14] = in[3][2];
	matrix[15] = in[3][3];
	btTransform  trans;
	trans.setFromOpenGLMatrix(&matrix[0]);

	return trans;

}