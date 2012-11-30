#include <freeglut.h>

#pragma once
class Ocean
{
public:
	Ocean(void);
	Ocean(int sizeT);
	~Ocean(void);
	void display(void);
	void genMap(int size);
	void update();
	void setShader(void);
private:
	void calculateNormals(int size);
	void drawVertex(int x , int y);
	GLfloat xPosition;
	GLfloat yPosition;
	GLfloat zPosition;
	GLuint texName;
	GLfloat scale;
	GLfloat timer;
	GLuint shaderProgram;
	GLuint vertexShader;
	GLuint fragShader;
	GLint timeUniform;
	GLint textureUniform;
};