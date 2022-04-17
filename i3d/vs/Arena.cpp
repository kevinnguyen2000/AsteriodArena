#include "Arena.h"

Arena::Arena() {
	this->width = 0;
	this->height = 0;
	this->circleWorldPosition = new Vector();
	// Set arena size
	this->arenaSize = new Vector();

	// Set circle radius
	this->circleRadius = 70;

	// Set wall colour to white
	this->leftWallColour = 1;
	this->rightWallColour = 1;
	this->topWallColour = 1;
	this->bottomWallColour = 1;

	this->collision = false;
}

Arena::~Arena() {
	
}

void Arena::setArena(int width, int height) {
	this->width = width;
	this->height = height;
}


void Arena::display() {

	// background color
	glClearColor(0, 0, 0.05, 1.0f);

	// Left border
	glColor3f(1.0, leftWallColour, leftWallColour);
	glPointSize(2.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(-width/2, height/2, 0.5);
	glVertex3f(-width/2, -height/2, 0.5);
	glEnd();

	// Top border 
	glColor3f(1.0, topWallColour, topWallColour);
	glPointSize(2.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(-width/2, height/2, 0.5);
	glVertex3f(width/2, height/2, 0.5);
	glEnd();

	// Right border
	glColor3f(1.0, rightWallColour, rightWallColour);
	glPointSize(2.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(width/2, height/2, 0.5);
	glVertex3f(width/2, -height/2, 0.5);
	glEnd();

	// Bottom border
	glColor3f(1.0, bottomWallColour, bottomWallColour);
	glPointSize(2.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(-width, -height/2, 0.5);
	glVertex3f(width/2, -height/2, 0.5);
	glEnd();

	// Set arena size for vectors
	arenaSize->setX(width);
	arenaSize->setY(height);
}

void Arena::setCircleWorldPositionVector(Vector* positionVector) {
	circleWorldPosition->setX(positionVector->getX());
	circleWorldPosition->setY(positionVector->getY());
}

void Arena::checkWallCollision() {
	// check left wall
	float leftWall = -arenaSize->getX() / 2;
	if (circleWorldPosition->getX() - circleRadius < leftWall) {
		leftWallColour = 0;
	}
	else {
		leftWallColour = 1;
	}
	if (circleWorldPosition->getX() < leftWall) {
		collision = true;
	}
	// check top wall
	float topWall = arenaSize->getY() / 2;
	if (circleWorldPosition->getY() + circleRadius > topWall) {
		topWallColour = 0;
	}
	else {
		topWallColour = 1;
	}
	if (circleWorldPosition->getY() > topWall) {
		collision = true;
	}
	// check right wall
	float rightWall = arenaSize->getX() / 2;
	if (circleWorldPosition->getX() + circleRadius > rightWall) {
		rightWallColour = 0;
	}
	else {
		rightWallColour = 1;
	}
	if (circleWorldPosition->getX() > rightWall) {
		collision = true;
	}
	// check bottom wall
	float bottomWall = -arenaSize->getY() / 2;
	if (circleWorldPosition->getY() - circleRadius < bottomWall) {
		bottomWallColour = 0;
	}
	else {
		bottomWallColour = 1;
	}
	if (circleWorldPosition->getY() < bottomWall) {
		collision = true;
	}
}

bool Arena::getCollision() {
	return collision;
}

void Arena::setCollisionFalse() {
	collision = false;
}

int Arena::getArenaHeight() {
	return height;
}

int Arena::getArenaWidth() {
	return width;
}
