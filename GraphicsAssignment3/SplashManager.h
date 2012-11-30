#include <freeglut.h>

#pragma once
class SplashManager
{
public:
	SplashManager(void);
	SplashManager(int x, int y, int z);
	~SplashManager(void);
	void display(void);
	void update(void);
	GLuint emitterX ,emitterY, emitterZ;
private:
	void createParticle(int i);
	GLuint texName;
};