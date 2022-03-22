#include "Player.h"

Player::Player() {

}

Player::~Player() {

}

void Player::display() {

	// pivot point offset
	const float model_offset = 0.0f;
	// first vertex - local coordinate
	const float v1x = 0.0f + model_offset;
	const float v1y = 1.0f + model_offset;
	// second vertex - local coordinate
	const float v2x = 1.0f + model_offset;
	const float v2y = -0.5f + model_offset;
	// third vertex - local coordinate
	const float v3x = -1.0f + model_offset;
	const float v3y = -0.5f + model_offset;

	// Red triangle - local coordinates
	// This renders the triangle in its local-coordinate frame
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(v1x, v1y, 0.0);
	glVertex3f(v2x, v2y, 0.0);
	glVertex3f(v3x, v3y, 0.0);
	glEnd();
	// this is just so we can see where its pointing
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(model_offset, model_offset, 0.0);
	glVertex3f(v1x, v1y, 0.0);
	glEnd();
	glPopMatrix();

}

void Player::setPlayerInitalPosition(int intialX, int initalY) {

}
