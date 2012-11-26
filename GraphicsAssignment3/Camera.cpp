/*		CAMERA CLASS
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class provides matrix manipulations to provide control over a camera type system
 * by manipulating  the viewport. 
 * It also provides controls for the camera manipulation.
 * 
 * Last Updated: 22/10/2012
*/

#define _USE_MATH_DEFINES // Allows me to use PI constant

#include "Camera.h"

#include <math.h>
#include <stdlib.h>
#include <freeglut.h>


//Values taken from setting the camera at a good starting position manually in the program.
GLfloat xPosition = 2.312;
GLfloat yPosition = 13.4;
GLfloat zPosition = 16.97;
GLfloat xRotation = 29;
GLfloat yRotation = 0;
GLfloat angle =0.0;

GLfloat radius = 10.0f; // This is used to allow the camera to rotate around a point slightly in front of it. Looks Smoother.

GLfloat lastX;
GLfloat lastY;



Camera::Camera(void)
{
}

Camera::~Camera(void)
{
}


void Camera::update()
{
	glTranslatef(0.0f, 0.0f, -radius);
    glRotatef(xRotation,1.0,0.0,0.0);
    
    glRotatef(yRotation,0.0,1.0,0.0);  
    glTranslated(-xPosition,-yPosition,-zPosition); 
}


void Camera::keyboardControl(unsigned char key, int x, int y) 
{
    if (key=='x') // Tilt camera up
    {
		xRotation += 1;
		if (xRotation >360)
		{
			xRotation -= 360;
		}
    }

    if (key=='z')// Tilt camera down
    {
		xRotation -= 1;
		if (xRotation < -360) 
		{
			xRotation += 360;
		}
    }

	if (key=='r') // Move up 
    {
		yPosition += 0.1f;
	}

	if (key=='f') // Move down  
    {
		yPosition -= 0.1f;
	}

	if (key=='e') // Look Left
    {
		yRotation -= 1;
		if (yRotation < -360)
		{
			yRotation += 360;
		}
	}

	if (key=='q') //  Look Right
    {
		yRotation += 1;
		if (yRotation < -360) 
		{
			yRotation += 360;
		}
    }

    if (key=='w') // Move forward in direction you are looking
    {
		GLfloat xRoationRadius;
		GLfloat yRotationRadius;
		yRotationRadius = (yRotation / 180 * M_PI); 
		xRoationRadius = (xRotation / 180 * M_PI); 
		xPosition += GLfloat(sin(yRotationRadius)) * 2;
		zPosition -= GLfloat(cos(yRotationRadius))* 2;
		yPosition -= GLfloat(sin(xRoationRadius))* 2;
    }

    if (key=='s')// Move back in direction you are looking
    {
		GLfloat xRoationRadius;
		GLfloat yRotationRadius;
		yRotationRadius = (yRotation / 180 * M_PI);
		xRoationRadius = (xRotation / 180 * M_PI); 
		xPosition -= float(sin(yRotationRadius));
		zPosition += float(cos(yRotationRadius));
		yPosition += float(sin(xRoationRadius));
    }

    if (key=='d') // Strafe to the Right
    {
		GLfloat yRotationRadius;
		yRotationRadius = (yRotation / 180 * M_PI);
		xPosition += GLfloat(cos(yRotationRadius)) * 0.2;
		zPosition += GLfloat(sin(yRotationRadius)) * 0.2;
    }

    if (key=='a') // Strafe to the Left
    {
		GLfloat yRotationRadius;
		yRotationRadius = (yRotation / 180 * M_PI);
		xPosition -= GLfloat(cos(yRotationRadius)) * 0.2;
		zPosition -= GLfloat(sin(yRotationRadius)) * 0.2;
    }
}