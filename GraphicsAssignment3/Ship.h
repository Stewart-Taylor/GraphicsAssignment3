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
	private:
		void GetFaces();
		unsigned int m_TotalFaces;
		Lib3dsFile * m_model;
		GLuint m_VertexVBO, m_NormalVBO, m_TexCoordVBO;
		GLuint texName;
		GLfloat xPosition, yPosition, zPosition;
		GLfloat xAngle, yAngle, zAngle;
		GLfloat scale;
		GLfloat timer;
};

