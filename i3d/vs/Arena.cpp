#include "Arena.h"

Arena::Arena(int width, int height) {
	this->width = width;
	this->height = height;
	fprintf(stderr, "WIDTH AND HEIGHT(%d, %d)\n", width, height);
}

Arena::~Arena() {
	
}

Arena::Arena(Arena& other) {
	this->width = other.width;
	this->height = other.height;
}


void Arena::display() {

	// clears previous renders if existed
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	/*
	// One pixel stars
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	glVertex3f(100, 100, -0.75);
	glVertex3f(200, 100, -0.75);
	glVertex3f(-100, -100, -0.75);
	glEnd();

	// Larger star
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(5, -5, -0.5);
	glVertex3f(-5, -5, -0.5);
	glVertex3f(-5, 5, -0.5);
	glVertex3f(5, 5, -0.5);
	glEnd();
	*/

	// Left border
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(2.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(0, 864, 0.5);
	glVertex3f(0, 0, 0.5);
	glEnd();

	// Top border 
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(2.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(0, 864, 0.5);
	glVertex3f(1536, 864, 0.5);
	glEnd();

	// Right border
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(2.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(1536, 864, 0.5);
	glVertex3f(1536, 0, 0.5);
	glEnd();

	// Bottom border
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(2.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0.5);
	glVertex3f(1536, 0, 0.5);
	glEnd();

	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
}
