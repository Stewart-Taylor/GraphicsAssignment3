/*		Ocean CLASS
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class generates Procedurally Generated Ocean 
 * It also simulates the oceans animation
 * This ocean makes extensive use of vertex and fragment shaders
 * 
 * Last Updated: 27/11/2012
*/

#include <glew.h>
#include <freeglut.h>
#include <math.h>
#include <time.h>
#include "Ocean.h"
#include "TextureLoader.h"
#include "NormalHelper.h"
#include "ShaderLoader.h"
  
GLfloat heightPoints[161+1][161+1];
GLfloat seascO[161+1][161+1];
GLfloat cd[161+1];
GLfloat normals[161+1][161+1][3];


Ocean::Ocean()
{

}

Ocean::Ocean(int size)
{
	xPosition = -400;
	yPosition = 0;
	zPosition = -400;
	scale = 5;
	timer = 0;

	for (int x = 0; x <= size; x++)
	{
		cd[x] = x;
	}

	texName = TextureLoader::loadTexture("Textures\\water3.bmp");

	genMap(size);
}


void Ocean::setShader()
{
	char *vs = NULL,*fs = NULL,*fs2 = NULL;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	vs = ShaderLoader::textFileRead("Shaders/Ocean.vert");
	fs = ShaderLoader::textFileRead("Shaders/Ocean.frag");

	const char * vv = vs;
	const char * ff = fs;

	glShaderSource(vertexShader, 1, &vv,NULL);
	glShaderSource(fragShader, 1, &ff,NULL);

	free(vs);
	free(fs);

	glCompileShader(vertexShader);
	glCompileShader(fragShader);

	vertexShaderProgram = glCreateProgram();
	glAttachShader(vertexShaderProgram,vertexShader);
	glAttachShader(vertexShaderProgram,fragShader);

	glLinkProgram(vertexShaderProgram);
	myUniformLocation = glGetUniformLocation(vertexShaderProgram, "time");
	myUniformLocationTex = glGetUniformLocation(vertexShaderProgram, "tex");
}

Ocean::~Ocean(void)
{

}


void Ocean::genMap(int mapSize)
{	
	srand(time(0));
	int random_seed = rand();
	srand(random_seed);

	for (int i = 0; i <= mapSize; i++)
	{
		for (int j = 0; j <= mapSize; j++)
		{
			int rSize = ((rand()%20)+2);
			heightPoints[i][j] = (float)rand()/((float)RAND_MAX/2.11f);
			seascO[i][j] = heightPoints[i][j];
		}
	}

	update();
}


void Ocean::calculateNormals(int size)
{
	int i, j;
	float v1[3],v2[3],out[3];
	v1[0] = cd[1];
	v1[1] = 0;
	v2[0] = 0;
	v2[1] = cd[1];
	for (j = 0; j < size; j++)
      for (i = 0; i < size; i++) {
		  v1[2] = heightPoints[i+1][j] - heightPoints[i][j];
          v2[2] = heightPoints[i][j+1] - heightPoints[i][j];
		  NormalHelper::normcrossprod(v1,v2,out);
		  normals[i][j][0] = -out[0];
		  normals[i][j][1] = -out[1];
		  normals[i][j][2] = -out[2];
	  }
   for (j = 0; j < size; j++) {
	  normals[size][j][0] = normals[size-1][j][0];
      normals[size][j][1] = normals[size-1][j][1];
      normals[size][j][2] = normals[size-1][j][2];
	  }
   for (i = 0; i < size; i++) {
	  normals[i][size][0] = normals[i][size-1][0];
	  normals[i][size][1] = normals[i][size-1][1];
	  normals[i][size][2] = normals[i][size-1][2];
	  }
   normals[size][size][0] = normals[size-1][size-1][0];
   normals[size][size][1] = normals[size-1][size-1][1];
   normals[size][size][2] = normals[size-1][size-1][2];
}


void Ocean::display(void)
{
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texName);

	glUseProgram(vertexShaderProgram);
	glUniform1f(myUniformLocation, timer);
	glUniform1i(texName, 0);

	int size = 161;

	glPushMatrix(); 

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_MODELVIEW);

	glTranslated(xPosition ,yPosition ,zPosition);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslated(0,0 ,0);
	glScaled(scale ,scale ,1);

   for (int j = 0; j < size; j++)
      for (int i = 0; i < size; i++)
	  {
		  glBegin(GL_POLYGON);
		  drawVertex(i,j);
		  glEnd();
	  }
      glEnd();  

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glUseProgram(0);
}



void Ocean::drawVertex(int i , int j)
{
	glNormal3fv(&normals[i][j][0]);		glTexCoord2f(0,0);	glVertex3f(cd[i],cd[j],-heightPoints[i][j]);
	glNormal3fv(&normals[i+1][j][0]);	glTexCoord2f(1,0);	glVertex3f(cd[i+1],cd[j],-heightPoints[i+1][j]);
	glNormal3fv(&normals[i+1][j+1][0]); glTexCoord2f(1,1);	glVertex3f(cd[i+1],cd[j+1],-heightPoints[i+1][j+1]);
	glNormal3fv(&normals[i][j+1][0]);	glTexCoord2f(0,1);	glVertex3f(cd[i],cd[j+1],-heightPoints[i][j+1]);
}


void Ocean::update()
{
	timer+= 1;

	calculateNormals(161); // MOVE TO VERTEX SHADER
}