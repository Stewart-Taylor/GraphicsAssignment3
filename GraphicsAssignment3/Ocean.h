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
	void getColor(GLfloat color[4], int x , int y);
	void calculateColors(int size);
	double distanceT(double dX0, double dY0, double dX1, double dY1);
	GLfloat xPosition;
	GLfloat yPosition;
	GLfloat zPosition;
	GLuint texName;
	GLfloat scale;
	GLfloat timer;
	GLuint vertexShaderProgram;
	GLuint vertexShader;
	GLint myUniformLocation;
};