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
	void adjustAmplitude(GLfloat amount);
	GLfloat getAmplitude(void);
private:
	void calculateNormals(int size);
	void drawVertex(int x , int y);
	GLfloat xPosition, yPosition, zPosition;
	GLuint texName;
	GLfloat scale;
	GLfloat timer;
	GLuint shaderProgram;
	GLuint vertexShader;
	GLuint fragShader;
	GLint timeUniform;
	GLint textureUniform;
	GLint amplitudeUniform;
	GLfloat amplitude;
};