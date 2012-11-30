#include <freeglut.h>

#pragma once
class CannonManager
{
public:
	CannonManager(void);
	CannonManager(int x , int y , int z);
	~CannonManager(void);
	void display(void);
	void update(void);
	void fire(GLfloat x, GLfloat y , GLfloat z);
	bool active;
private:
	void createParticle(int i);
	GLuint texName;
	GLfloat emitterX;
	GLfloat emitterY;
	GLfloat emitterZ;
};
