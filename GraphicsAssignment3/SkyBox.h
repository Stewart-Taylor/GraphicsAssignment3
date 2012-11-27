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
	GLuint textureLeft;
	GLuint textureMiddle;
	GLuint textureTop;
	GLuint textureInnerRight;
	GLuint textureRight;
};