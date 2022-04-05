#include "Player.h"

Player::Player() {
	// Set angle
	this->angle = 0;
	// Vector for postion
	this->positionVector = new Vector();
	// Vector for angle
	this->directionVector = new Vector();

	/*
	// Set x coordinate
	this->positonVector.push_back(0);
	// Set y coordinate
	this->positonVector.push_back(0);
	// Set starting angle so player faces up
	this->directionVector.push_back(0);
	*/
}

Player::~Player() {

}

void Player::display() {

	// Red triangle - local coordinates
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
	// assign in new angle.
	
}

void Player::rotateRight() {
	// sets turn angle
	angle = angle - 5;
	// assign in new angle.
	
}

