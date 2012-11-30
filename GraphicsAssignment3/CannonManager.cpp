/*		Cannon Manager
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class is used to generate the smoke from a cannon being fired
 * It uses particle effects to produce this effect
 *
 * Last Updated: 30/11/2012
*/

#include "CannonManager.h"
#include "TextureLoader.h"
#include <freeglut.h>

struct Particle
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat timer;
	GLfloat limit;
	GLfloat direction[3];
	GLfloat scale;
	bool active;
	GLfloat color[4];
};

Particle smokeParticles[600];

CannonManager::CannonManager(void)
{

}

CannonManager::CannonManager(int x , int y , int z)
{
	emitterX = x;
	emitterY = y;
	emitterZ = z;
	active = false;

	for(int i = 0 ; i < 600 ; i++)
	{
		createParticle(i);
		smokeParticles[i].timer = 9999;
	}

	texName = TextureLoader::loadTexture("Textures\\smoke.bmp");
}

CannonManager::~CannonManager(void)
{

}

void  CannonManager::fire(GLfloat x , GLfloat y , GLfloat z)
{
	emitterX = x + 17;
	emitterY = y;
	emitterZ = z + 10;

	for(int i = 0; i<600 ;i++)
	{
		createParticle(i);
	}
}

void CannonManager::createParticle(int i)
{
	 smokeParticles[i].x = emitterX + (float)rand()/((float)RAND_MAX/2) - (float)rand()/((float)RAND_MAX/2);
	 smokeParticles[i].y = emitterY - (float)rand()/((float)RAND_MAX/2);
	 smokeParticles[i].z = emitterZ + (float)rand()/((float)RAND_MAX/2) - (float)rand()/((float)RAND_MAX/2);
	 smokeParticles[i].timer = (rand()%100); 
	 smokeParticles[i].limit = 70;
	 smokeParticles[i].direction[0] = 0.01 + (float)rand()/((float)RAND_MAX/0.603f);
	 smokeParticles[i].direction[1] = (float)rand()/((float)RAND_MAX/0.08f) - (float)rand()/((float)RAND_MAX/0.08f);
	 smokeParticles[i].direction[2] = (float)rand()/((float)RAND_MAX/0.08f) - (float)rand()/((float)RAND_MAX/0.08f);
	 smokeParticles[i].scale = (float)rand()/((float)RAND_MAX/0.9f);
	 smokeParticles[i].active = true;
	 smokeParticles[i].color[0] = 0;
	 smokeParticles[i].color[1] = 0;
	 smokeParticles[i].color[2] = 0;
	 smokeParticles[i].color[3] = 1;
}


void CannonManager::display(void)
{
	glEnable(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
 
	glPushMatrix(); 

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texName);

	glTranslated(-15 ,0 ,-15);
	glTranslated(0,0 ,0);
	glScaled(1.0 ,1.0  ,1.0 );

	for(int i = 0; i<600 ;i++)
	{
		if( smokeParticles[i].timer < smokeParticles[i].limit)
		{
			glPushMatrix(); 

			glTranslated(smokeParticles[i].x ,smokeParticles[i].y ,smokeParticles[i].z);
			glScaled(smokeParticles[i].scale ,smokeParticles[i].scale ,smokeParticles[i].scale);

			glBegin (GL_QUADS);
			glColor4f( smokeParticles[i].color[0] ,smokeParticles[i].color[1], smokeParticles[i].color[2] , smokeParticles[i].color[3]);	
			glTexCoord2d (0, 0);  glVertex3f (-1, -1, 0);
			glTexCoord2d (1, 0);  glVertex3f (1, -1, 0);
			glTexCoord2d (1, 1);  glVertex3f (1, 1, 0);
			glTexCoord2d (0, 1);  glVertex3f (-1, 1, 0);
			glEnd();

			glPopMatrix();
		}
	}

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

void CannonManager::update(void)
{
	for(int i = 0; i<600 ;i++)
	{
		smokeParticles[i].timer++;

		if( smokeParticles[i].timer < smokeParticles[i].limit)
		{
			float perc = smokeParticles[i].timer / smokeParticles[i].limit;

			smokeParticles[i].x += smokeParticles[i].direction[0];
			smokeParticles[i].y += smokeParticles[i].direction[1];
			smokeParticles[i].z += smokeParticles[i].direction[2];

			if(perc < 0.7)
			{
				smokeParticles[i].color[0] =  0.37f;
				smokeParticles[i].color[1] = 0.21f; 
				smokeParticles[i].color[2] = 0.1f; 
			}
			else
			{
				smokeParticles[i].color[0] = (1-perc);
				smokeParticles[i].color[1] =  (1-perc);
				smokeParticles[i].color[2] = (1-perc);
			}

			smokeParticles[i].color[3] = (1-perc);
			smokeParticles[i].scale += 0.01f;
		}
	}
}