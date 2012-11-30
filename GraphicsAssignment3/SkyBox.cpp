/*		SkyBox Class
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class is used as a skybox , Updated to support cube mapped textures
 *
 * Last Updated: 28/11/2012
*/

#include "SkyBox.h"
#include "TextureLoader.h"
#include <stdio.h>	
#include <freeglut.h>


SkyBox::SkyBox(void)
{
	scale = 800; 

	textureLeft = TextureLoader::loadTextureClamped("Textures\\left.bmp");
	textureMiddle= TextureLoader::loadTextureClamped("Textures\\middle.bmp");
	textureTop= TextureLoader::loadTextureClamped("Textures\\top.bmp");
	textureInnerRight= TextureLoader::loadTextureClamped("Textures\\innerRight.bmp");
	textureRight= TextureLoader::loadTextureClamped("Textures\\right.bmp");
}

SkyBox::~SkyBox(void)
{
}

void SkyBox::display(void)
{
	glPushMatrix(); 

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glMatrixMode(GL_MODELVIEW);

	glTranslated(0 ,90.0 ,0);
	glScaled(scale ,scale ,scale);

	glBindTexture(GL_TEXTURE_2D, textureRight);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0);		glVertex3f(  0.5, -0.5, -0.5 );      
	glTexCoord2f(1.0,  1.0);	glVertex3f(  0.5,  0.5, -0.5 );     
	glTexCoord2f(0.0,  1.0);	glVertex3f( -0.5,  0.5, -0.5 );      
	glTexCoord2f(0.0, 0.0);		glVertex3f( -0.5, -0.5, -0.5 );      
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureMiddle);

	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0);		glVertex3f(  0.5, -0.5, 0.5 );
	glTexCoord2f(1.0,  1.0);	glVertex3f(  0.5,  0.5, 0.5 );
	glTexCoord2f(0.0,  1.0);	glVertex3f( -0.5,  0.5, 0.5 );
	glTexCoord2f(0.0, 0.0);		glVertex3f( -0.5, -0.5, 0.5 );
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureInnerRight);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0);		glVertex3f( 0.5, -0.5, -0.5 );
	glTexCoord2f(1.0,  1.0);	glVertex3f( 0.5,  0.5, -0.5 );
	glTexCoord2f(0.0,  1.0);	glVertex3f( 0.5,  0.5,  0.5 );
	glTexCoord2f(0.0, 0.0);		glVertex3f( 0.5, -0.5,  0.5 );
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureLeft);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0);		glVertex3f( -0.5, -0.5,  0.5 );
	glTexCoord2f(1.0,  1.0);	glVertex3f( -0.5,  0.5,  0.5 );
	glTexCoord2f(0.0,  1.0);	glVertex3f( -0.5,  0.5, -0.5 );
	glTexCoord2f(0.0, 0.0);		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();
 
	glBindTexture(GL_TEXTURE_2D, textureTop);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0);		glVertex3f(  0.5,  0.5,  0.5 );
	glTexCoord2f(1.0,  1.0);	glVertex3f(  0.5,  0.5, -0.5 );
	glTexCoord2f(0.0,  1.0);	glVertex3f( -0.5,  0.5, -0.5 );
	glTexCoord2f(0.0, 0.0);		glVertex3f( -0.5,  0.5,  0.5 );
	glEnd();
 
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}