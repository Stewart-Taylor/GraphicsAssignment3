/*	 Sailing Ship
 *	Graphics Assignment 3
 *
 *	AUTHOR: STEWART TAYLOR
 *	DATE STARTED: 30/11/2012
 *------------------------------------
 * This program is part of the Graphics modules third assignment.
 * It demonstrates the use of shaders vertex and fragment and all previous knowledge 
 * 
 * The main class is used as a controller and is also used to set the program up.
 *
 * Last Updated: 30/11/2012
*/

#include <glew.h>
#include <freeglut.h>
#include <fstream>
#include <iostream>
#include "Camera.h"
#include "Main.h"
#include "SkyBox.h"
#include "Plane.h"
#include "Ocean.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"
#include "Ship.h"
#include "SplashManager.h"
#include "ShadowHelper.h"
#include "OverlayPlane.h"
#include "CannonManager.h"
#include "CannonBall.h"

Camera camera = Camera();

SkyBox skybox;
Plane plane;
Ocean ocean;
Ship ship = Ship("Models/Galleon.3ds");
SplashManager splashManager;
OverlayPlane overlay;
CannonManager cannon;
CannonBall cannonBall;

GLuint v,f,f2,p;

GLfloat specular = 1.0;
GLfloat diffuse = 0.5;
GLfloat shiny = 50.0;
GLfloat light_position[] = { 28.0 , -406.0 ,-31.0 , 1.0};
GLfloat mat_specular[] = { specular, specular, specular, 1.0 };
GLfloat mat_diffuse[] = { diffuse, diffuse, 0.5, 1.0 };
GLfloat mat_shininess[] = { shiny };

GLint myUniformLocation;
GLint myUniformLocation2;
GLint myUniformLocation3;

float resX, resY;

bool overlayVisible = true;

void generateMap()
{
	ocean.genMap(64);
}

void setObjects(void)
{
	skybox =  SkyBox();
	plane = Plane();
	ocean = Ocean(161);
	cannon = CannonManager(0,0,0);
	cannonBall = CannonBall();
	overlay = OverlayPlane();
	splashManager = SplashManager(ship.xPosition + 15 , ship.yPosition + 4 , ship.zPosition + 15); 
	generateMap();
}

void init (void) 
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glCullFace(GL_FRONT);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	setObjects();
}


void setShaders() 
{
	ocean.setShader();
	overlay.setShader();
	ship.setShader();
	ship.CreateVBO();
}

void drawShadows()
{
	GLfloat shadow_proj[16];
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
    GLfloat plane_eq[] = {0.0, -8.2 , 0.0, 0.0};
	ShadowHelper::shadow_matrix(light_position,plane_eq,shadow_proj);
	glMultMatrixf(shadow_proj);

	ship.displayShadow();
	cannonBall.displayShadow();

	glPopMatrix();

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}


void display (void)
{
	glUseProgram(p);
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel (GL_SMOOTH);
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	camera.update();

	glDisable(GL_CULL_FACE);
	skybox.display();
	glEnable(GL_CULL_FACE);

	plane.display();
	ocean.display();

	glDisable(GL_CULL_FACE);

	drawShadows();
	splashManager.display();
	cannon.display();
	cannonBall.display();
	ship.display();
	
	if(overlayVisible == true)
	{
		overlay.display(resX , resY);
	}

	glutSwapBuffers();
}

void reshape (int w, int h)
{
	if( ( w > 400) && ( h > 400)) // Allows min window size , stops silly resizing
	{
		glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
		glMatrixMode (GL_PROJECTION); //set the matrix to projection
		glLoadIdentity ();
		gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1600.0); //set the perspective (angle of sight, width, height, , depth)
		glMatrixMode (GL_MODELVIEW); //set the matrix back to model

		resX = w;
		resY = h;
	}
}

void overlayToggle()
{
	if( overlayVisible == true)
	{
		overlayVisible = false;
	}
	else
	{
		overlayVisible = true;
	}
}

void fireCannon()
{
	if( (cannonBall.active == false) && ( cannonBall.splashActive == false) && ( cannon.active == false))
	{
		cannon.fire(ship.xPosition , ship.yPosition , ship.zPosition);
		cannonBall.fire(ship.xPosition , ship.yPosition , ship.zPosition);
	}
}

void keyboard (unsigned char key, int x, int y)
{
	key = tolower(key); // Allows Caps Lock to still work

	camera.keyboardControl(key , x , y);

	if (key=='k'){light_position[1] += 1;}
	if (key=='i'){light_position[1] -= 1;}
	if (key=='j'){light_position[0] += 1;}
	if (key=='l'){light_position[0] -= 1;}
	if (key=='u'){light_position[2] += 1;}
	if (key=='o'){light_position[2] -= 1;}

	if (key=='g')
	{
		overlayToggle();
	}

	if (key=='h')
	{
		fireCannon();
	}


	if (key=='m')
	{
		ocean.adjustAmplitude(0.01f);
	}

	if (key=='n')
	{
		ocean.adjustAmplitude(-0.01f);
	}
}

void mouseUpdate(int x , int y)
{
	//camera.mouseControl(x,y);
}

void idle(void)
{
	ocean.update();
	ship.update(ocean.getAmplitude());
	splashManager.emitterX = ship.xPosition + 15;
	splashManager.emitterY = ship.yPosition + 4;
	splashManager.emitterZ = ship.zPosition + 15;
	splashManager.update();
	cannon.update();
	cannonBall.update();
	glutPostRedisplay();
}

void printInfo()
{
	std::cout << "	Sailing Ship - Graphics Assignment 3" << std::endl << std::endl;
	std::cout << "	Created by Stewart Taylor" << std::endl << std::endl;
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "CONTROLS" << std::endl;
	std::cout << std::endl;
	std::cout << "CAMERA" << std::endl;
	std::cout << " W,A,S,D  - Move Camera" << std::endl;
	std::cout << " Q,E - Look Left/Right" << std::endl;
	std::cout << " R,F - Move Camera Up/Down " << std::endl;
	std::cout << " Z,X - Tilt Camera Up/Down" << std::endl;
	std::cout << std::endl;
	std::cout << "Other" << std::endl;
	std::cout << " G - Enable Overlay Effect" << std::endl;
	std::cout << " H - Fire Cannon" << std::endl;
	std::cout << " M - Increase Ocean Amplitude" << std::endl;
	std::cout << " N - Decrease Ocean Amplitude" << std::endl;
	std::cout << std::endl;
}

int main (int argc, char **argv)
{
	printInfo();
    glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (600, 600); 
    glutInitWindowPosition (200, 100);
    glutCreateWindow ("3D Sailing Ship"); 
    init (); 
    glutDisplayFunc (display); 
    glutIdleFunc (idle); 
    glutReshapeFunc (reshape);
	glutPassiveMotionFunc(mouseUpdate); 
    glutKeyboardFunc (keyboard); 
	glewInit();
	if (glewIsSupported("GL_VERSION_2_0"))
		printf("Ready for OpenGL 2.0\n");
	else {
		printf("OpenGL 2.0 not supported\n");
		exit(1);
	}
	setShaders(); 
	glutMainLoop(); 
    return 0;
}