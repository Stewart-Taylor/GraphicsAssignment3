/*		SkyBox lass
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class is used as a skybox
 *
 * Last Updated: 22/10/2012
*/

#include "SkyBox.h"
#include "TextureLoader.h"

#include <stdio.h>	
#include <freeglut.h>


SkyBox::SkyBox(void)
{
	scale = 800; // it's a good size
	//texName = TextureLoader::loadTexture("Textures\\CloudsTile.bmp");



	 texLeft = TextureLoader::loadTextureClamped("Textures\\left.bmp");
	 texMiddle= TextureLoader::loadTextureClamped("Textures\\middle.bmp");
	 texTop= TextureLoader::loadTextureClamped("Textures\\top.bmp");
	 texInnerRight= TextureLoader::loadTextureClamped("Textures\\innerRight.bmp");
	 texRight= TextureLoader::loadTextureClamped("Textures\\right.bmp");

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


	glScaled(scale ,scale ,scale);


	glBindTexture(GL_TEXTURE_2D, texRight);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0);	glVertex3f(  0.5, -0.5, -0.5 );      
	glTexCoord2f(1.0,  1.0);	glVertex3f(  0.5,  0.5, -0.5 );     
	glTexCoord2f(0.0,  1.0);   glVertex3f( -0.5,  0.5, -0.5 );      
	glTexCoord2f(0.0, 0.0);	glVertex3f( -0.5, -0.5, -0.5 );      
	glEnd();

	
	glBindTexture(GL_TEXTURE_2D, texMiddle);

	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0);		glVertex3f(  0.5, -0.5, 0.5 );
	glTexCoord2f(1.0,  1.0);	glVertex3f(  0.5,  0.5, 0.5 );
	glTexCoord2f(0.0,  1.0);	glVertex3f( -0.5,  0.5, 0.5 );
	glTexCoord2f(0.0, 0.0);		glVertex3f( -0.5, -0.5, 0.5 );
	glEnd();

	
 

	glBindTexture(GL_TEXTURE_2D, texInnerRight);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0);		glVertex3f( 0.5, -0.5, -0.5 );
	glTexCoord2f(1.0,  1.0);	glVertex3f( 0.5,  0.5, -0.5 );
	glTexCoord2f(0.0,  1.0);	glVertex3f( 0.5,  0.5,  0.5 );
	glTexCoord2f(0.0, 0.0);		glVertex3f( 0.5, -0.5,  0.5 );
	glEnd();

	
 
	glBindTexture(GL_TEXTURE_2D, texLeft);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0);		glVertex3f( -0.5, -0.5,  0.5 );
	glTexCoord2f(1.0,  1.0);	glVertex3f( -0.5,  0.5,  0.5 );
	glTexCoord2f(0.0,  1.0);	glVertex3f( -0.5,  0.5, -0.5 );
	glTexCoord2f(0.0, 0.0);		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();
 

	glBindTexture(GL_TEXTURE_2D, texTop);
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