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

	// pivot point offset
	const float model_offset = 0.0f;
	// top vertex - local coordinate
	const float v1x = 0.0f + model_offset;
	const float v1y = 0.0625f + model_offset;
	// bottom right vertex - local coordinate
	const float v2x = 0.02f + model_offset;
	const float v2y = -0.0275f + model_offset;
	// bottom vertex - local coordinate
	const float v3x = 0.0f + model_offset;
	const float v3y = -0.01f + model_offset;
	// bottom left - local coordinate
	const float v4x = -0.02f + model_offset;
	const float v4y = -0.0275f + model_offset;

	// Red triangle - local coordinates
	// This renders the triangle in its local-coordinate frame
	glPushMatrix();
	glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	//glScalef(0.2f, 0.2f, 0.2f);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	/*
	glVertex3f(v1x, v1y, 0.0);
	glVertex3f(v2x, v2y, 0.0);
	glVertex3f(v3x, v3y, 0.0);
	glVertex3f(v4x, v4y, 0.0);
	*/
	glVertex3f(-10, 0, 0.0);
	glVertex3f(0, -10, 0.0);
	glVertex3f(10, 0, 0.0);
	glVertex3f(0, 10, 0.0);
	glEnd();
	// this is just so we can see where its pointing
	/*
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(model_offset, model_offset, 0.0);
	glVertex3f(v1x, v1y, 0.0);
	glEnd();
	// make outline of spaceship
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.5, 1.0);
	glVertex3f(v1x, v1y, 0.0);
	glVertex3f(v2x, v2y, 0.0);
	glVertex3f(v3x, v3y, 0.0);
	glVertex3f(v4x, v4y, 0.0);

	glEnd();
	*/
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

