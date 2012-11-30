/*		Surface Normal Helper
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class is used to help calculate surface normals. 
 * It uses the cross product.
 *
 * Last Updated: 22/10/2012
*/

#include "NormalHelper.h"
#include <math.h>
#include <stdlib.h>

NormalHelper::NormalHelper(void)
{
}

NormalHelper::~NormalHelper(void)
{
}

void NormalHelper::getSurfaceNormal(GLfloat *normalVector,GLfloat vertexA[3],GLfloat vertexB[3],GLfloat vertexC[3])
{
	GLfloat vectorTemp[2][3];
	GLuint a;
	GLuint b;
	GLfloat vertexTemp[3][3];

	for (a=0;a<3;++a)
	{
		vertexTemp[0][a]=vertexA[a];
		vertexTemp[1][a]=vertexB[a]; 
		vertexTemp[2][a]=vertexC[a];
	}

	for (a=0; a<2; ++a)								
	{													
		for (b=0; b<3; ++b)
		{
			vectorTemp[a][b]=vertexTemp[2-a][b]-vertexTemp[0][b];			
		}
	}

	crossProduct(normalVector,vectorTemp[0],vectorTemp[1]);	
	normalize(normalVector);	

}

void NormalHelper::normalize(GLfloat * vector)
{
	GLfloat length;
	GLuint a;

	length=sqrt(pow(vector[0],2) + pow(vector[1],2) + pow(vector[2],2));

	for (a=0;a<3;++a)// Divide by it's length to normalize
	{
		vector[a]/=length;
	}
}

void NormalHelper::crossProduct(GLfloat *c,GLfloat a[3], GLfloat b[3])
{															
	c[0]=a[1]*b[2] - b[1]*a[2];
	c[1]=a[2]*b[0] - b[2]*a[0];
	c[2]=a[0]*b[1] - b[0]*a[1];
}


void NormalHelper::normcrossprod(float v1[3], float v2[3], float out[3])
{
	out[0] = v1[1]*v2[2] - v1[2]*v2[1];
	out[1] = v1[2]*v2[0] - v1[0]*v2[2];
	out[2] = v1[0]*v2[1] - v1[1]*v2[0];
	normalize2(out);
}


void NormalHelper::normalize2(float v[3]) {
	GLfloat d = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	v[0] /= d; v[1] /= d; v[2] /= d;
}