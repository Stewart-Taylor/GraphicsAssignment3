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
	GLfloat xPosition;
	GLfloat yPosition;
	GLfloat zPosition;
	GLfloat scale;
	GLuint vertexShaderProgram;
	GLuint fragShader;
	GLint myUniformLocation , myUniformLocation2 , myUniformLocation3;
	float timer;
};

