/*		CannonBall Class
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class is used genereates and simulates the flight of a cannonball
 * It also produces a splash effect when it collides
 *
 * Last Updated: 30/11/2012
*/

#define _USE_MATH_DEFINES // Allows me to use PI constant 

#include "CannonBall.h"
#include "TextureLoader.h"
#include <stdio.h>	
#include <math.h>

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
	GLfloat color[4];
};

Particle splashParticles[200];

typedef struct 
{
  double x;
  double y;
  double z;
} Vertex;


CannonBall::CannonBall()
{
	xPosition = 0;
	yPosition = 0;
	zPosition = 0;
	scale = 1.0;

	texName = TextureLoader::loadTexture("Textures\\splash.bmp");
}

CannonBall::~CannonBall(void)
{
}


void CannonBall::createSplash()
{
	splashActive = true;

	for(int i = 0; i<200 ;i++)
	{
		createParticle(i);
	}
}

void CannonBall::createParticle(int i)
{
	 splashParticles[i].x = xPosition + (float)rand()/((float)RAND_MAX/2) - (float)rand()/((float)RAND_MAX/2);
	 splashParticles[i].y = yPosition;
	 splashParticles[i].z = zPosition + (float)rand()/((float)RAND_MAX/2) - (float)rand()/((float)RAND_MAX/2);
	 splashParticles[i].timer = (rand()%100); 
	 splashParticles[i].limit = 60;
	 splashParticles[i].direction[0] = (float)rand()/((float)RAND_MAX/0.08f) - (float)rand()/((float)RAND_MAX/0.08f) ;
	 splashParticles[i].direction[1] = (float)rand()/((float)RAND_MAX/0.08f)  ;
	 splashParticles[i].direction[2] = (float)rand()/((float)RAND_MAX/0.08f) - (float)rand()/((float)RAND_MAX/0.08f) ;
	 splashParticles[i].scale  = (float)rand()/((float)RAND_MAX/0.9f) ;
	 splashParticles[i].xAngle = (float)rand()/((float)RAND_MAX/360);
	 splashParticles[i].yAngle = (float)rand()/((float)RAND_MAX/360);
	 splashParticles[i].zAngle = (float)rand()/((float)RAND_MAX/360);
	 splashParticles[i].color[0] = 0;
	 splashParticles[i].color[1] = 0;
	 splashParticles[i].color[2] = 0;
	 splashParticles[i].color[3] = 1;
}

void CannonBall::fire(GLfloat x ,GLfloat y, GLfloat z )
{
	xPosition = x +4;
	yPosition = y +2;
	zPosition = z -3;

	xDirection = 0.6;
	yDirection = 0.1;
	zDirection = (float)rand()/((float)RAND_MAX/0.08f) - (float)rand()/((float)RAND_MAX/0.08f) ;

	scale = 0.4;
	timer = 0;
	active = true;
}

void CannonBall::display(void)
{
	if( active == true)
	{
		glEnable(GL_LIGHTING);
		glPushMatrix(); 

		Vertex c;
		c.x = 0;
		c.y = 0;
		c.z = 0;

		glColor4f( 0.4, 0.4, 0.4 , 1.0);

		glMatrixMode(GL_MODELVIEW);

		glTranslated(xPosition ,yPosition ,zPosition);
	
		glTranslated(0,0 ,0);
		glScaled(scale ,scale ,scale);

		GLfloat radius = 1.0;
		GLuint slices = 70;

		GLuint i,j;
		GLdouble phi1,phi2,theta, s, t;
		Vertex e,p;

		for (j=0;j <= slices; j++) 
		{
			phi1 = j * (2* M_PI) / slices;
			phi2 = (j + 1) * (2* M_PI) / slices;	

			glBegin(GL_QUAD_STRIP);
			for (i=0;i <= slices;i++) 
			{
				theta = i * M_PI / slices;

				e.x = sin ( theta ) * cos ( phi2 );
				e.y = sin ( theta ) * sin ( phi2 );
				e.z = cos ( theta );
				p.x = c.x + radius * e.x;
				p.y = c.y + radius * e.y;
				p.z = c.z + radius * e.z;

				glNormal3f(e.x,e.y,e.z);
				s = phi2 / (2* M_PI);         
				t = 1 - theta/M_PI;       
				glTexCoord2f(s, t);
				glVertex3f(p.x,p.y,p.z);

				e.x = sin ( theta ) * cos ( phi1 );
				e.y = sin ( theta ) * sin ( phi1 );
				e.z = cos ( theta );
				p.x = c.x + radius * e.x;
				p.y = c.y + radius * e.y;
				p.z = c.z + radius * e.z;

				glNormal3f(e.x,e.y,e.z);
				s = phi1/(2* M_PI);       
				t = 1 - theta/M_PI;      
				glTexCoord2f(s, t);
 
				glVertex3f(p.x,p.y,p.z);
		  }
		  glEnd();
	   }
		glPopMatrix();
	}

	displaySplash();
}

void CannonBall::displaySplash(void)
{
	if( splashActive == true)
	{
		glEnable(GL_COLOR_BUFFER_BIT );
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
 
		glPushMatrix(); 

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D); 
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, texName);

		glScaled(1.0 ,1.0  ,1.0 );

		for(int i = 0; i<200 ;i++)
		{
			if( splashParticles[i].timer < splashParticles[i].limit)
			{
				glPushMatrix(); 

				glTranslated(splashParticles[i].x ,splashParticles[i].y ,splashParticles[i].z);
				glRotatef(splashParticles[i].xAngle,1.0 ,0.0 ,0.0);
				glRotatef(splashParticles[i].yAngle,0.0 ,1.0 ,0.0);
				glRotatef(splashParticles[i].zAngle,0.0 ,0.0 ,1.0);
				glScaled(splashParticles[i].scale ,splashParticles[i].scale ,splashParticles[i].scale);

				glBegin (GL_QUADS);
				glColor4f( splashParticles[i].color[0] ,splashParticles[i].color[1], splashParticles[i].color[2] , splashParticles[i].color[3] );	
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
}

void CannonBall::displayShadow(void)
{
	if( active == true)
	{
		glPushMatrix(); 

		Vertex c;
		c.x = 0;
		c.y = 0;
		c.z = 0;

		glMatrixMode(GL_MODELVIEW);

		glTranslated(xPosition ,yPosition ,zPosition);
		glTranslated(0,0 ,0);
		glScaled(scale ,scale ,scale);
		glColor4f(0.1,0.1,0.1,0.3);	     

		GLfloat r = 1.0;
		GLuint n = 20;

		GLuint i,j;
		GLdouble phi1,phi2,theta, s, t;
		Vertex e,p;

	   for (j=0;j <= n; j++) 
	   {
		  phi1 = j * (2*M_PI) / n;
		  phi2 = (j + 1) * (2*M_PI) / n;	

		  glBegin(GL_QUAD_STRIP);
		  for (i=0;i <= n;i++) {
			 theta = i * M_PI / n;

			e.x = sin ( theta ) * cos ( phi2 );
		e.y = sin ( theta ) * sin ( phi2 );
			e.z = cos ( theta );
			p.x = c.x + r * e.x;
			p.y = c.y + r * e.y;
			p.z = c.z + r * e.z;

			s = phi2 / (2*M_PI);         
			t = 1 - theta/M_PI;        
			glVertex3f(p.x,p.y,p.z);

			e.x = sin ( theta ) * cos ( phi1 );
			e.y = sin ( theta ) * sin ( phi1 );
			e.z = cos ( theta );
			p.x = c.x + r * e.x;
			p.y = c.y + r * e.y;
			p.z = c.z + r * e.z;

			s = phi1/(2*M_PI);       
			t = 1 - theta/M_PI; 
 
			glVertex3f(p.x,p.y,p.z);
		  }
		  glEnd();
	   }

		glPopMatrix();
	}
}

void CannonBall::update()
{
	if(active == true)
	{
		xPosition += xDirection;
		yPosition += yDirection;
		zPosition += zDirection;

		yDirection -= 0.002;

		if( yPosition < 0)
		{
			active = false;
			createSplash();
			timer = 0;
		}
	}

	updateSplash();
}

void CannonBall::updateSplash(void)
{
	if( splashActive == true)
	{
		timer += 1;

		if( timer > 1000)
		{
			splashActive = false;
		}

		for(int i = 0; i<200 ;i++)
		{
			splashParticles[i].timer++;

			if( splashParticles[i].timer < splashParticles[i].limit)
			{
				float perc = splashParticles[i].timer / splashParticles[i].limit;

				splashParticles[i].x += splashParticles[i].direction[0];
				splashParticles[i].y += splashParticles[i].direction[1];
				splashParticles[i].z += splashParticles[i].direction[2];

				splashParticles[i].color[0] = (1-perc);
				splashParticles[i].color[1] =  (1-perc);
				splashParticles[i].color[2] = (1-perc);
			
				if(perc > 0.5)
				{
					splashParticles[i].y -= 0.1;
				}

				splashParticles[i].color[3] = (1-perc);
				splashParticles[i].scale += 0.01f;
			}
		}
	}
}