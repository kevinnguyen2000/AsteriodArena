#include "Arena.h"
#include <iostream>


using namespace std;

Arena::Arena() {

}

void Arena::display() {

	// One pixel stars
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	glVertex3f(-0.25, -0.3, -0.75);
	glVertex3f(0.85, -0.25, -0.75);
	glVertex3f(0.75, 0.75, -0.75);
	glVertex3f(-0.4, 0.75, -0.75);
	glVertex3f(-0.7, -0.7, -0.75);
	glVertex3f(-0.8, 0.1, -0.75);
	glVertex3f(0.05, 0.4, -0.75);
	glVertex3f(0.2, -0.6, -0.75);
	glVertex3f(0.3, 0.7, -0.75);
	glEnd();

	// Larger star
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, 0.49, -0.5);
	glVertex3f(-0.495, 0.49, -0.5);
	glVertex3f(-0.495, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glEnd();

	// Larger star
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, 0.49, -0.5);
	glVertex3f(-0.495, 0.49, -0.5);
	glVertex3f(-0.495, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glEnd();

	// Larger star
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.3, 0.3, -0.5);
	glVertex3f(0.305, 0.3, -0.5);
	glVertex3f(0.305, 0.29, -0.5);
	glVertex3f(0.3, 0.29, -0.5);
	glEnd();

	// Larger star
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.1, -0.19, -0.5);
	glVertex3f(0.105, -0.19, -0.5);
	glVertex3f(0.105, -0.2, -0.5);
	glVertex3f(0.1, -0.2, -0.5);
	glEnd();

	// Larger star
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.6, -0.49, -0.5);
	glVertex3f(0.605, -0.49, -0.5);
	glVertex3f(0.605, -0.5, -0.5);
	glVertex3f(0.6, -0.5, -0.5);
	glEnd();

	// Larger star
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.605, -0.46, -0.5);
	glVertex3f(-0.61, -0.46, -0.5);
	glVertex3f(-0.61, -0.47, -0.5);
	glVertex3f(-0.605, -0.47, -0.5);
	glEnd();


	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();

}
