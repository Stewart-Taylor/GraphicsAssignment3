/*		Plane CLASS
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * Generates a blue plane with graident and surface normals.
 * 
 * Last Updated: 26/11/2012
*/

#include "Plane.h"
#include <freeglut.h>

Plane::Plane(void)
{
	xPosition = 0;
	yPosition = -8.2;
	zPosition = 0;
	scale = 800;
}

Plane::~Plane(void)
{
}

void Plane::display(void)
{
	glDisable(GL_LIGHTING);
	glPushMatrix(); 
	glMatrixMode(GL_MODELVIEW);

	glTranslated(xPosition ,yPosition ,zPosition);
	glScaled(scale ,scale ,scale);

	glBegin(GL_POLYGON);
	glColor3f( 1.0 ,0.98, 0.9 );	
	glVertex3f(  0.5, 0.0, -0.5 );      
	glVertex3f(  0.5,  0.0, 0.5 );     
	glVertex3f( -0.5,  0.0, 0.5 );      
	glVertex3f( -0.5, 0.0, -0.5 );      
	glEnd();

	glPopMatrix();
	glEnable(GL_LIGHTING);
}	