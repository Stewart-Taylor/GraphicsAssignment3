/*		OverlayPlane CLASS
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * Generates a plane in which to provide overlay effects
 * Uses fragment shader to enable this
 * 
 * Last Updated: 30/11/2012
*/

#include <glew.h>
#include <freeglut.h>
#include "OverlayPlane.h"
#include "ShaderLoader.h"

OverlayPlane::OverlayPlane(void)
{
	xPosition = 0;
	yPosition = 8.2;
	zPosition = 0;
	scale = 1;
	timer = 0;
}

OverlayPlane::~OverlayPlane(void)
{
}


void OverlayPlane::setShader(void)
{
	char *vs = NULL,*fs = NULL,*fs2 = NULL;

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	fs = ShaderLoader::textFileRead("Shaders/Overlay.frag");


	const char * ff = fs;

	glShaderSource(fragShader, 1, &ff,NULL);

	free(vs);
	free(fs);

	glCompileShader(fragShader);

	vertexShaderProgram = glCreateProgram();
	glAttachShader(vertexShaderProgram,fragShader);

	glLinkProgram(vertexShaderProgram);
	myUniformLocation = glGetUniformLocation(vertexShaderProgram, "timer");
	myUniformLocation2 = glGetUniformLocation(vertexShaderProgram, "resX");
	myUniformLocation3 = glGetUniformLocation(vertexShaderProgram, "resY");
}

void OverlayPlane::display(GLfloat resX , GLfloat resY)
{
	timer += 1.0f;
	

	glUseProgram(vertexShaderProgram);
	glUniform1f(myUniformLocation, timer);
	glUniform1f(myUniformLocation2, resX);
	glUniform1f(myUniformLocation3, resY);


	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDisable(GL_LIGHTING);
	glPopMatrix(); // Required
	glPushMatrix(); 
	glMatrixMode (GL_PROJECTION);
	
	glColor3f( 0.0 ,0.0, 0.0 ); 
	 
	glTranslated(0 ,0 ,0);
//	glScaled(scale ,scale ,scale);
	

	glBegin(GL_POLYGON);
	glVertex3f( -19.5, -19.5, 29.5);       
	glVertex3f( -14.5,  19.5, 15.5);      
	glVertex3f(  19.5,  19.5, 15.5);      
	glVertex3f(  23.5, -19.5, 29.5);     
	glEnd();


	glPopMatrix();
	glEnable(GL_LIGHTING);


	glUseProgram(0);
}	
