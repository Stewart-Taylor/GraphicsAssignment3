#include <freeglut.h>

#pragma once
class TextureLoader
{
public:
	TextureLoader(void);
	~TextureLoader(void);
	static GLuint loadTexture(char* filePath);
};