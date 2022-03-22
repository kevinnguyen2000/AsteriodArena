#include "Arena.h"

Arena::Arena() {
	
	this->width = 0;
	this->height = 0;
	
}

Arena::~Arena() {
	
}

Arena::Arena(Arena& other) {
	this->width = other.width;
	this->height = other.height;
}

void Arena::setArena(int width, int height) {
	this->width = width;
	this->height = height;
	//fprintf(stderr, "w and h(%d, %d)\n", width, height);
}


void Arena::display() {

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
	glVertex3f(0, height, 0.5);
	glVertex3f(0, 0, 0.5);
	glEnd();

	// Top border 
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(2.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(0, height, 0.5);
	glVertex3f(width, height, 0.5);
	glEnd();

	// Right border
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(2.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(width, height, 0.5);
	glVertex3f(width, 0, 0.5);
	glEnd();

	// Bottom border
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(2.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0.5);
	glVertex3f(width, 0, 0.5);
	glEnd();
}
