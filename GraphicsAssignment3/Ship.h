#include <lib3ds/file.h>
#include <lib3ds/mesh.h>
#include <freeglut.h>

#pragma once
class Ship
{
	public:
		Ship(char* filename);
		~Ship();
		void display();
		void CreateVBO();
		void update(GLfloat oceanAmplitude);
		GLfloat xPosition, yPosition, zPosition;
		void displayShadow();
		void setShader(void);
	private:
		void getFaces();
		unsigned int m_TotalFaces;
		Lib3dsFile * m_model;
		GLuint m_VertexVBO, m_NormalVBO, m_TexCoordVBO;
		GLuint texName, texName2;
		GLfloat xAngle, yAngle, zAngle;
		GLfloat scale;
		GLfloat timer;
		GLuint shaderProgram;
		GLuint fragShader;
		GLint timeUniform;
		GLint textureUniform;
};

