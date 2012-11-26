#include <freeglut.h>

#pragma once
class SkyBox
{
public:
	SkyBox(void);
	~SkyBox(void);
	void display(void);
private:
	GLfloat scale;
	GLuint texLeft;
	GLuint texMiddle;
	GLuint texTop;
	GLuint texInnerRight;
	GLuint texRight;
};