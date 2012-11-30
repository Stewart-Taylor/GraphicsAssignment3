#include <freeglut.h>

#pragma once
class CannonBall
{
public:
	CannonBall();
	~CannonBall(void);
	void display(void);
	void displayShadow(void);
	void update();
	void fire(GLfloat x ,GLfloat y, GLfloat z );
private:
	void createParticle(int i);
	void createSplash();
	void displaySplash(void);
	void updateSplash(void);
	GLfloat xPosition, yPosition, zPosition;
	GLfloat xDirection, yDirection, zDirection;
	GLfloat scale;
	GLuint texName;
	bool active;
	bool splashActive;
	int timer ;
};
