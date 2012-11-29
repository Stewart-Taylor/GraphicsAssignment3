/*	Graphics Assignment 3
 *	AUTHOR: STEWART TAYLOR
 *	DATE STARTED: 24/11/2012
 *------------------------------------
 * This program is part of the Graphics modules third assignment.
 * It demonstrates the use of shaders vertex and fragment 
 * 
 * The main class is used as a controller and is also used to set the program up.
 *
 * Last Updated: 27/11/2012
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

Camera camera = Camera();

SkyBox skybox;
Plane plane;
Ocean ocean;
Ship ship =  Ship("Models/Galleon.3ds");
SplashManager splashManager;
OverlayPlane overlay;

GLuint v,f,f2,p;

GLfloat specular = 1.0;
GLfloat diffuse = 0.5;
GLfloat shiny = 50.0;
GLfloat light_position[] = { 28.0 , -106.0 ,-31.0 , 1.0};
GLfloat mat_specular[] = { specular, specular, specular, 1.0 };
GLfloat mat_diffuse[] = { diffuse, diffuse, 0.5, 1.0 };
GLfloat mat_shininess[] = { shiny };

GLint myUniformLocation;
GLint myUniformLocation2;
GLint myUniformLocation3;

float resX;
float resY;

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


void setShaders() {

	ocean.setShader();
	overlay.setShader();
	ship.setShader();
	ship.CreateVBO();
	
/*	char *vs = NULL,*fs = NULL,*fs2 = NULL;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
	f2 = glCreateShader(GL_FRAGMENT_SHADER);


	vs = ShaderLoader::textFileRead("shaders/toon.vert");
	fs = ShaderLoader::textFileRead("shaders/toon.frag");
	fs2 =ShaderLoader::textFileRead("shaders/toon2.frag");

	const char * ff = fs;
	const char * ff2 = fs2;
	const char * vv = vs;

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);
	glShaderSource(f2, 1, &ff2,NULL);

	free(vs);free(fs);

	glCompileShader(v);
	glCompileShader(f);
	glCompileShader(f2);

	p = glCreateProgram();
	glAttachShader(p,f);
	glAttachShader(p,f2);
	glAttachShader(p,v);

	glLinkProgram(p);
	//glUseProgram(p);


	 myUniformLocation = glGetUniformLocation(p, "referenceTex");
	 myUniformLocation2 = glGetUniformLocation(p, "pixelWidth");
	 myUniformLocation3 = glGetUniformLocation(p, "pixelHeight");

	 */
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

	
//	ship.DrawRef();
	ship.DrawShadow();
	//uranusPole.displayShadow();  
	//saturnPole.displayShadow();
	//jupiterPole.displayShadow();
	//marsPole.displayShadow();
	//earthPole.displayShadow();
	//venusPole.displayShadow();
	//mercuryPole.displayShadow();

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
	
	ship.Draw();


	if(overlayVisible == true)
	{
		overlay.display(resX , resY);
	}

	glutSwapBuffers();
}

void reshape (int w, int h)
{

	if( ( w > 400) && ( h > 400)) // Allows min window size
	{

		glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
		glMatrixMode (GL_PROJECTION); //set the matrix to projection
		glLoadIdentity ();
		gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1600.0); //set the perspective (angle of sight, width, height, , depth)
		glMatrixMode (GL_MODELVIEW); //set the matrix back to model

		resX = w;
		resY = w;

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
}

void mouseUpdate(int x , int y)
{
	//camera.mouseControl(x,y);
}

void idle(void)
{
	ocean.update();
	ship.update();
	splashManager.emitterX = ship.xPosition + 15;
	splashManager.emitterY = ship.yPosition + 4;
	splashManager.emitterZ = ship.zPosition + 15;
	splashManager.update();
	glutPostRedisplay();
}

void printInfo()
{
	std::cout << "	ASeS 3" << std::endl << std::endl;
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
	std::cout << "LIGHT " << std::endl;
	std::cout << " U,I,K,L,J - Move Light Source" << std::endl;
	std::cout << std::endl;
}

int main (int argc, char **argv)
{
	printInfo();
    glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (600, 600); 
    glutInitWindowPosition (200, 100);
    glutCreateWindow ("3D Procedural Volcanic Island"); 
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
	glutMainLoop (); 
    return 0;
}