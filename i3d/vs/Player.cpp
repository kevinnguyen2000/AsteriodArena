#include "Player.h"

Player::Player() {
	// Intialise Math helper class
	this->math = new Math();
	this->movementSpeed = 0;
	this->dt = 0;
	// Set angle
	this->angle = 90;
	// Vector for postion
	this->positionVector = new Vector();
	// Vector for angle
	this->directionVector = new Vector();
	*directionVector = math->degreeToDirectionVector(angle);
}

Player::~Player() {
}

void Player::display() {
	// This renders the triangle in its local-coordinate frame
	glPushMatrix();
	glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(positionVector->getX(), positionVector->getY(), 0.0f);
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
	// Set movement speed to 2500
	this->movementSpeed = 2500;

	Vector* newCoords = new Vector();
	newCoords->setX(positionVector->getX() + directionVector->getX() * movementSpeed * dt);
	newCoords->setY(positionVector->getY() + directionVector->getY() * movementSpeed * dt);
	
	positionVector->setX(newCoords->getX());
	positionVector->setY(newCoords->getY());
	//printf("Positionvector, X and Y: (%f, %f)\n", positionVector->getX(), positionVector->getY());
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

void Player::setDt(float dt) {
	this->dt = dt;
}

Vector Player::getPositionVector() {
	return *positionVector;
}

Vector Player::getDirectionVector() {
	return *directionVector;
}

void Player::resetPlayer() {
	movementSpeed = 0;
	angle = 90;
	positionVector->setX(0);
	positionVector->setY(0);
	*directionVector = math->degreeToDirectionVector(angle);
}

