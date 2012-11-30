#include <freeglut.h>

#pragma once
class OverlayPlane
{
public:
	OverlayPlane(void);
	~OverlayPlane(void);
	void display(GLfloat resX , GLfloat resY);
	void setShader(void);
private:
	GLfloat xPosition, yPosition, zPosition;
	GLfloat scale;
	GLuint shaderProgram;
	GLuint fragShader;
	GLint timerUniform , resXUniform, resYUniform;
	float timer;
};

