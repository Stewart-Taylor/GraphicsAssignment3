#include <freeglut.h>

#pragma once
class ShadowHelper
{
public:
	ShadowHelper(void);
	~ShadowHelper(void);
	static void shadow_matrix(GLfloat lt[4],GLfloat pl[4],GLfloat shadow_proj[16]);
};