#include "Player.h"

Player::Player() {
	// Set angle
	this->angle = 90;
	// Vector for postion
	this->positionVector = new Vector();
	// Vector for angle
	this->directionVector = new Vector();
	// Intialise Math helper class
	this->math = new Math();
}

Player::~Player() {
}

void Player::display() {
	// This renders the triangle in its local-coordinate frame
	glPushMatrix();
	glLoadIdentity();

	//glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glScalef(1.5f, 1.5f, 1.5f);

	glBegin(GL_TRIANGLES);
	// Front of ship
	glVertex3f(0, 8, 0.0);
	glVertex3f(10, 0, 0.0);
	glVertex3f(0, -8, 0.0);

	// Left side of ship
	glVertex3f(-10, 10, 0.0);
	glVertex3f(0, 8, 0.0);
	glVertex3f(0, 0, 0.0);

	// Right side of ship
	glVertex3f(-10, -10, 0.0);
	glVertex3f(0, -8, 0.0);
	glVertex3f(0, 0, 0.0);

	glEnd();
	
	// this is just so we can see where its pointing
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(4, 0, 0.0);
	glVertex3f(10, 0, 0.0);
	glEnd();

	// make outline of spaceship
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.25, 1.0);
	glVertex3f(-10, 10, 0.0);
	glVertex3f(0, 8, 0.0);
	glVertex3f(10, 0, 0.0);
	glVertex3f(0, -8, 0.0);
	glVertex3f(-10, -10, 0.0);
	glVertex3f(0, 0, 0.0);

	glEnd();
	glPopMatrix();
}

void Player::moveFoward() {
	printf("move foward ");
}

void Player::rotateLeft() {
	// sets turn angle
	angle = angle + 5;
	// check for overflow
	if (angle >= 360) {
		angle = 0;
	}
	// assign in new angle to Player direction vector
	*directionVector = math->degreeToDirectionVector(angle);
}

void Player::rotateRight() {
	// sets turn angle
	angle = angle - 5;
	// check for overflow
	if (angle <= -360) {
		angle = 0;
	}
	// assign in new angle to Player direction vector
	*directionVector = math->degreeToDirectionVector(angle);
	// tester
	/*
	printf("Directionvector, X and Y: (%f, %f)\n", directionVector->getX(), directionVector->getY());
	*/
}

