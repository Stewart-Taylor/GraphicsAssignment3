/*		Ship CLASS
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class loads in a 3ds model
 * It loads in vertex data and texture coords
 * It uses the lib3ds library to calculate normals for the model
 * It also simulates the ships movement in an ocean environment
 *
 * Reference for model loading : Lib3ds tutorial: My first model , http://www.donkerdump.nl/node/207 , only covers vertex loading
 * Normals are caluclated through lib3ds library
 * Required additon of texture capabilty as tutorial only covers loading of vertexes
 * 
 * Last Updated: 30/11/2012
 */

#include <glew.h>
#include <lib3ds/file.h>
#include <lib3ds/mesh.h>
#include <freeglut.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include "Ship.h"
#include "TextureLoader.h"
#include "ShaderLoader.h"

Ship::Ship(char* filename)
{
	xPosition = 0;
	yPosition = 0;
	zPosition = -40;
	xAngle = -90;
	yAngle = 0;
	zAngle = 0;
	scale = 1;
	timer = 0;

	m_TotalFaces = 0;
	m_model = lib3ds_file_load(filename);
	if(!m_model)
	{
		throw strcat("Unable to load ", filename);
	}
}

Ship::~Ship()
{
	
}

void Ship::setShader(void)
{
	char *vs = NULL,*fs = NULL,*fs2 = NULL;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	fs = ShaderLoader::textFileRead("Shaders/water.frag");
	const char * ff = fs;
	glShaderSource(fragShader, 1, &ff,NULL);

	free(vs);
	free(fs);

	glCompileShader(fragShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,fragShader);

	glLinkProgram(shaderProgram);
	timeUniform = glGetUniformLocation(shaderProgram, "timer");
	textureUniform= glGetUniformLocation(shaderProgram, "tex");
}

void Ship::CreateVBO()
{
	assert(m_model != NULL);
	
	getFaces(); // get faces count
	
	// Allocate memory for our vertices and normals
	Lib3dsVector * vertices = new Lib3dsVector[m_TotalFaces * 3];
	Lib3dsVector * normals = new Lib3dsVector[m_TotalFaces * 3];
	Lib3dsTexel* texCoords = new Lib3dsTexel[m_TotalFaces * 3];
	
	Lib3dsMesh * mesh;
	unsigned int FinishedFaces = 0;

	for(mesh = m_model->meshes;mesh != NULL;mesh = mesh->next)
	{
		lib3ds_mesh_calculate_normals(mesh, &normals[FinishedFaces*3]);

		for(unsigned int cur_face = 0; cur_face < mesh->faces;cur_face++)
		{
			Lib3dsFace * face = &mesh->faceL[cur_face];
			for(unsigned int i = 0;i < 3;i++)
			{
				if(mesh->texels) 
				{
					memcpy(&texCoords[FinishedFaces*3 + i], mesh->texelL[face->points[ i ]], sizeof(Lib3dsTexel)); 
				}
				memcpy(&vertices[FinishedFaces*3 + i], mesh->pointL[face->points[i]].pos, sizeof(Lib3dsVector));
			}
			FinishedFaces++;
		}
	}
	
	// Generate a Vertex Buffer Object and store it with our vertices
	glGenBuffers(1, &m_VertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Lib3dsVector) * 3 * m_TotalFaces, vertices, GL_STATIC_DRAW);
	
	// Generate another Vertex Buffer Object and store the normals in it
	glGenBuffers(1, &m_NormalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_NormalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Lib3dsVector) * 3 * m_TotalFaces, normals, GL_STATIC_DRAW);

    glGenBuffers(1, &m_TexCoordVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Lib3dsTexel) * 3 * m_TotalFaces, texCoords, GL_STATIC_DRAW);

	delete vertices;
	delete normals;
	lib3ds_file_free(m_model);
	m_model = NULL;

	texName = TextureLoader::loadTexture("Textures\\Galleon.bmp");
	texName2 = TextureLoader::loadTexture("Textures\\water3.bmp");
}

// Counts the total number of faces this model has
void Ship::getFaces()
{
	assert(m_model != NULL);
	
	m_TotalFaces = 0;
	Lib3dsMesh * mesh;

	for(mesh = m_model->meshes;mesh != NULL;mesh = mesh->next)
	{
		m_TotalFaces += mesh->faces;
	}
}

void Ship::display() 
{
	glColor3f( 1.0 ,1.0, 1.0 ); 
	glEnable(GL_LIGHTING);
	glPushMatrix(); 

	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texName);

	glTranslated(xPosition ,yPosition ,zPosition);
	glRotatef(xAngle, 1.0, 0.0, 0.0);
	glRotatef(yAngle, 0.0, 1.0, 0.0);
	glRotatef(zAngle, 0.0, 0.0, 1.0);
	glTranslated(0,0 ,0);
	glScaled(scale ,scale ,scale);

	assert(m_TotalFaces != 0);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); 
	
	// Bind Buffers
	glBindBuffer(GL_ARRAY_BUFFER, m_NormalVBO);
	glNormalPointer(GL_FLOAT, 0, NULL);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordVBO);    
    glTexCoordPointer(2, GL_FLOAT, 0, NULL); 

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexVBO);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	//Render the triangles
	glDrawArrays(GL_TRIANGLES, 0, m_TotalFaces * 3);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); 

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Ship::displayShadow() //Projected Method
{
	glColor4f(0.1,0.1,0.1,0.1);	
	glPushMatrix(); 

	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, texName);

	glTranslated(xPosition ,yPosition ,zPosition);
	glRotatef(xAngle, 1.0, 0.0, 0.0);
	glRotatef(yAngle, 0.0, 1.0, 0.0);
	glRotatef(zAngle, 0.0, 0.0, 1.0);
	glTranslated(0,0 ,0);
	glScaled(scale ,scale ,scale);

	assert(m_TotalFaces != 0);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); 
	
	// Bind Buffers
	glBindBuffer(GL_ARRAY_BUFFER, m_NormalVBO);
	glNormalPointer(GL_FLOAT, 0, NULL);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordVBO);    
    glTexCoordPointer(2, GL_FLOAT, 0, NULL); 

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexVBO);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	// Render the triangles
	glDrawArrays(GL_TRIANGLES, 0, m_TotalFaces * 3);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); 

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Ship::update(GLfloat oceanAmplitude) 
{
	timer += 0.0001f;

	//Ship Movement
	yPosition =  -( (0.5 + oceanAmplitude)  *sin(timer * 100));
	xAngle = -90 - ((2 + oceanAmplitude)  *sin(timer * 100)) * -sin(timer * 100) ; //Ship rocking
	zAngle = ((2 + oceanAmplitude) *sin(timer * 100)) * -sin(timer * 100);
	zPosition += 0.03f;

	if( zPosition > 315) // Resets it , stops it going through skybox and to the scary  world beyond
	{
		zPosition = -40;
	}
}