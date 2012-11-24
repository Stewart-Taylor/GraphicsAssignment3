/*	Assignment 3
 *	AUTHOR: STEWART TAYLOR
 *	DATE STARTED: 16/11/2012
 *------------------------------------
 * This program is part of the Graphics modules third assignment.
 * It demonstrates the use of shaders vertex and fragment 
 * 
 * The main class is used as a controller and is also used to set the program up.
 *
 * Last Updated: 23/11/2012
*/

#include <glew.h>
#include "Camera.h"
#include "Main.h"
#include "SkyBox.h"
#include "Plane.h"
#include "Ocean.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"
#include <freeglut.h>
#include <fstream>
#include <iostream>


Camera camera = Camera();

SkyBox skybox;
Plane plane;
Ocean ocean;

GLuint v,f,f2,p;

GLfloat specular = 1.0;
GLfloat diffuse = 0.5;
GLfloat shiny = 50.0;
GLfloat light_position[] = { 56.0 , 20.0 ,9.0 , 1.0};
GLfloat mat_specular[] = { specular, specular, specular, 1.0 };
GLfloat mat_diffuse[] = { diffuse, diffuse, 0.5, 1.0 };
GLfloat mat_shininess[] = { shiny };

GLint myUniformLocation;
GLint myUniformLocation2;
GLint myUniformLocation3;
float timer;

void generateMap()
{
	ocean.genMap(64);
}

void setObjects(void)
{
	skybox =  SkyBox();
	plane = Plane();
	ocean = Ocean(256);
	timer = 0;
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
	
	char *vs = NULL,*fs = NULL,*fs2 = NULL;

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
	glUseProgram(p);


	 myUniformLocation = glGetUniformLocation(p, "referenceTex");
	 myUniformLocation2 = glGetUniformLocation(p, "pixelWidth");
	 myUniformLocation3 = glGetUniformLocation(p, "pixelHeight");
}



void displayFog(void)
{
	GLfloat density = 0.002f;
	GLfloat fogColor[4] = {0.70f, 0.7f, 0.7f, 1.0f};
	glFogi (GL_FOG_MODE, GL_LINEAR);
	glFogfv (GL_FOG_COLOR, fogColor);
	glFogf (GL_FOG_DENSITY, density);
	glHint (GL_FOG_HINT, GL_NICEST);
	glFogf(GL_FOG_START, 100.0f);
	glFogf(GL_FOG_END, 600.0f); 
    glEnable(GL_FOG);
}


void display (void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel (GL_SMOOTH);

	displayFog();
	timer += 0.001f;
	glUniform1f(myUniformLocation, 1);
	glUniform1f(myUniformLocation2, 1);
	glUniform1f(myUniformLocation3, 1);

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

	glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1600.0); //set the perspective (angle of sight, width, height, , depth)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model
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

	if (key=='g'){generateMap();}
}

void mouseUpdate(int x , int y)
{
	//camera.mouseControl(x,y);
}

void idle(void)
{
//	ocean.update();
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
	std::cout << "Main " << std::endl;
	std::cout << " G - Generate Island" << std::endl;
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