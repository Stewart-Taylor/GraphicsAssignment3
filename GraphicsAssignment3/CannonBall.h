#include <freeglut.h>

#pragma once
class CannonBall
{
public:
	CannonBall();
	CannonBall(GLfloat x , GLfloat y , GLfloat z );
	~CannonBall(void);
	void display(void);
	void displayShadow(void);
	void setAngle(GLfloat xAngleT , GLfloat yAngleT , GLfloat zAngleT);
	void update();
	void fire(GLfloat x ,GLfloat y, GLfloat z );
private:
	GLfloat xPosition;
	GLfloat yPosition;
	GLfloat zPosition;
	GLfloat xAngle;
	GLfloat yAngle;
	GLfloat zAngle;
	GLfloat scale;
	GLuint texName;
	bool active;
	bool splashActive;
	GLfloat xDirection;
	GLfloat yDirection;
	GLfloat zDirection;
	int timer ;
	void createParticle(int i);
	void createSplash();
	void displaySplash(void);
	void updateSplash(void);
};
