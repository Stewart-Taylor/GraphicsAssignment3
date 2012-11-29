#include <lib3ds/file.h>
#include <lib3ds/mesh.h>
#include <freeglut.h>

#pragma once
class Ship
{
	public:
		Ship(char* filename);
		~Ship();
		void Draw();
		void CreateVBO();
		void update(void);
		GLfloat xPosition, yPosition, zPosition;
		void DrawRef();
		void DrawShadow();
		void setShader(void);
	private:
		void GetFaces();
		unsigned int m_TotalFaces;
		Lib3dsFile * m_model;
		GLuint m_VertexVBO, m_NormalVBO, m_TexCoordVBO;
		GLuint texName , texName2;
		GLfloat xAngle, yAngle, zAngle;
		GLfloat scale;
		GLfloat timer;
		GLuint vertexShaderProgram;
		GLuint fragShader;
		GLint myUniformLocation;
		GLint myUniformLocation2;
};

