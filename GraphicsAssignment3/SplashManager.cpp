/*		Splash Manager
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class is used to generate the smoke from a volcano
 * It also simulates wind
 *
 * Last Updated: 28/11/2012
*/

#include "SplashManager.h"
#include "TextureLoader.h"
#include <freeglut.h>


struct Particle
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat xAngle;
	GLfloat yAngle;
	GLfloat zAngle;
	GLfloat timer;
	GLfloat limit;
	GLfloat direction[3];
	GLfloat scale;
	bool active;
	GLfloat color[4];
};


Particle particles[400];

SplashManager::SplashManager(void)
{

}

SplashManager::SplashManager(int x , int y , int z)
{
	emitterX = x;
	emitterY = y;
	emitterZ = z;

	for(int i = 0 ; i < 400 ; i++)
	{
		createParticle(i);
		particles[i].timer = (rand()%1590);
	}

	texName = TextureLoader::loadTexture("Textures\\splash.bmp");
}

SplashManager::~SplashManager(void)
{
}

void SplashManager::createParticle(int i)
{

	if( (float)rand()/((float)RAND_MAX/100) > 50)
	{
		particles[i].x = emitterX + (float)rand()/((float)RAND_MAX/2) - (float)rand()/((float)RAND_MAX/2) ;
		particles[i].x += 6;

		particles[i].direction[0] = (float)rand()/((float)RAND_MAX/0.006f) ; //- (float)rand()/((float)RAND_MAX/0.02f) ;
		particles[i].direction[1] = -0.001f ; //(float)rand()/((float)RAND_MAX/0.02f) ;
		particles[i].direction[2] =  0 ;(float)rand()/((float)RAND_MAX/0.2f) - (float)rand()/((float)RAND_MAX/0.2f) ;
	
	}
	else
	{
		particles[i].x = emitterX + (float)rand()/((float)RAND_MAX/2) - (float)rand()/((float)RAND_MAX/2) ;
		particles[i].x -= 6;

		particles[i].direction[0] = -( (float)rand()/((float)RAND_MAX/0.006f)) ; //- (float)rand()/((float)RAND_MAX/0.02f) ;
		particles[i].direction[1] = -0.001f ; //(float)rand()/((float)RAND_MAX/0.02f) ;
		particles[i].direction[2] =  0 ;(float)rand()/((float)RAND_MAX/0.2f) - (float)rand()/((float)RAND_MAX/0.2f) ;

	}

	particles[i].y = 1;
	particles[i].z = emitterZ + (float)rand()/((float)RAND_MAX/20) - (float)rand()/((float)RAND_MAX/20) ;

	particles[i].timer = (rand()%100); 
	particles[i].limit = 1600;
	 
	 particles[i].scale = (float)rand()/((float)RAND_MAX/2.2f) ;
	 particles[i].active = true;
	 particles[i].color[0] = 0;
	 particles[i].color[1] = 0;
	 particles[i].color[2] = 0;
	 particles[i].color[3] = 1;
	 particles[i].xAngle =  90 ; 
	 particles[i].yAngle = 0; 
	 particles[i].zAngle = 0; 
}


void SplashManager::display(void)
{
	glEnable(GL_COLOR_BUFFER_BIT );
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
 
	glPushMatrix(); 

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texName);

	glTranslated(-15 ,0 ,-15);
	glTranslated(0,0 ,0);
	glScaled(1 ,1 ,1);


	for(int i = 0; i<400 ;i++)
	{
		glPushMatrix(); 

		glTranslated(particles[i].x ,particles[i].y ,particles[i].z);
		glRotatef(particles[i].xAngle, 1.0, 0.0, 0.0);
		glRotatef(particles[i].yAngle, 0.0, 1.0, 0.0);
		glRotatef(particles[i].zAngle, 0.0, 0.0, 1.0);
		glScaled(particles[i].scale ,particles[i].scale ,particles[i].scale);

		glBegin (GL_QUADS);
		glColor4f( particles[i].color[0] ,particles[i].color[1], particles[i].color[2] , particles[i].color[3] );	
		glTexCoord2d (0, 0);  glVertex3f (-1, -1, 0);
		glTexCoord2d (1, 0);  glVertex3f (1, -1, 0);
		glTexCoord2d (1, 1);  glVertex3f (1, 1, 0);
		glTexCoord2d (0, 1);  glVertex3f (-1, 1, 0);
		glEnd();
		
		glPopMatrix();
	}

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}


void SplashManager::reset(int x , int y , int z)
{
	emitterX = x;
	emitterY = y;
	emitterZ = z;

	for(int i = 0; i<400 ;i++)
	{
		particles[i].x = emitterX + (float)rand()/((float)RAND_MAX/2) - (float)rand()/((float)RAND_MAX/2) ;
		particles[i].y = emitterY ;
		particles[i].z = emitterZ + (float)rand()/((float)RAND_MAX/2) - (float)rand()/((float)RAND_MAX/2) ;
		particles[i].scale = 0.3;
	}
}


void SplashManager::update(void)
{
	for(int i = 0; i<400 ;i++)
	{
		particles[i].color[0] = 1.0;
		particles[i].color[1] =  1.0;
		particles[i].color[2] = 1.0;

		particles[i].timer++;

		if( particles[i].timer < particles[i].limit)
		{
			float perc = particles[i].timer / particles[i].limit;
		
			particles[i].x += particles[i].direction[0];
			particles[i].y += particles[i].direction[1];
			particles[i].z += particles[i].direction[2];

			
			particles[i].scale += 0.001f;

			particles[i].color[0] = (1.0 -perc);
			particles[i].color[1] = (1.0 -perc);
			particles[i].color[2] = (1.0 -perc);
			particles[i].color[3] = (1.0 -perc);
		}
		else
		{
			createParticle(i);
		}
	}
}