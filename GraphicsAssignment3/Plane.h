#include <freeglut.h>

#pragma once
class Plane
{
public:
	Plane(void);
	~Plane(void);
	void display(void);
private:
	GLfloat xPosition;
	GLfloat yPosition;
	GLfloat zPosition;
	GLfloat scale;
};