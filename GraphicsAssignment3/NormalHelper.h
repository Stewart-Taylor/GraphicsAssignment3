#pragma once

#include <freeglut.h>
class NormalHelper
{
public:
	NormalHelper(void);
	~NormalHelper(void);
	static void getSurfaceNormal(GLfloat *norm,GLfloat pointa[3],GLfloat pointb[3],GLfloat pointc[3]);
	static void normcrossprod(float v1[3], float v2[3], float out[3]);
private:
	static void normalize(GLfloat * vect); 
	static void crossProduct(GLfloat *c,GLfloat a[3], GLfloat b[3]);
	static void normalize2(float v[3]) ;
};