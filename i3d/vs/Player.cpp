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
	this->mulitpliedDirectionVector = new Vector();
	this->maxSpeed = 140;
	this->playerRadius = 15.0;
	this->gunType = "normal";
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
	glScalef(1.75f, 1.75f, 1.75f);

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

	glColor3f(0.5, 0.75, 1.0);

	glEnd();

	if (gunType == "normal") {
		// Gun display
		glColor3f(0.5, 0.75, 1.0);
		glBegin(GL_TRIANGLES);
		// Left side of gun
		glVertex3f(5, 4, 0.0);
		glVertex3f(10, 2, 0.0);
		glVertex3f(10, 0, 0.0);

		// Right side of gun
		glVertex3f(5, -4, 0.0);
		glVertex3f(10, -2, 0.0);
		glVertex3f(10, 0, 0.0);

		// Tip of gun
		glVertex3f(10, 2, 0.0);
		glVertex3f(13, 0, 0.0);
		glVertex3f(10, -2, 0.0);

		glEnd();

		// make outline gun
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
		glColor3f(0.4, 0.6, 0.8);
		glVertex3f(5, 4, 0.0);
		glVertex3f(10, 2, 0.0);
		glVertex3f(13, 0, 0.0);
		glVertex3f(10, -2, 0.0);
		glVertex3f(5, -4, 0.0);
		glVertex3f(10, 0, 0.0);
		glEnd();
	}
	
	if (gunType == "missile") {
		// Gun display
		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_TRIANGLES);
		// Left side of gun
		glVertex3f(5, 4, 0.0);
		glVertex3f(13, 2, 0.0);
		glVertex3f(10, 0, 0.0);

		// Right side of gun
		glVertex3f(5, -4, 0.0);
		glVertex3f(13, -2, 0.0);
		glVertex3f(10, 0, 0.0);

		// Tip of gun
		glVertex3f(13, 2, 0.0);
		glVertex3f(13, -2, 0.0);
		glVertex3f(10, 0, 0.0);

		glEnd();

		// make outline gun
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
		glColor3f(0.6, 0.6, 0.7);
		glVertex3f(5, 4, 0.0);
		glVertex3f(13, 2, 0.0);
		glVertex3f(13, -2, 0.0);
		glVertex3f(5, -4, 0.0);
		glVertex3f(10, 0, 0.0);
		glEnd();
	}
	
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
	if (movementSpeed <= maxSpeed) {
		this->movementSpeed = movementSpeed + 0.125;
	}
	else {
		this->movementSpeed = movementSpeed;
	}

	Vector* newCoords = new Vector();
	newCoords->setX(positionVector->getX() + directionVector->getX() * movementSpeed * dt);
	newCoords->setY(positionVector->getY() + directionVector->getY() * movementSpeed * dt);
	
	positionVector->setX(newCoords->getX());
	positionVector->setY(newCoords->getY());
}

void Player::slowDown() {
	if (movementSpeed >= 0) {
		this->movementSpeed = movementSpeed - 0.020;
	}
	else {
		this->movementSpeed = 0;
	}

	Vector* newCoords = new Vector();
	newCoords->setX(positionVector->getX() + directionVector->getX() * movementSpeed * dt);
	newCoords->setY(positionVector->getY() + directionVector->getY() * movementSpeed * dt);

	positionVector->setX(newCoords->getX());
	positionVector->setY(newCoords->getY());
}

void Player::rotateLeft() {
	// sets turn angle
	angle = angle + 0.125;
	// check for overflow
	if (angle >= 360) {
		angle = 0;
	}
	// assign in new angle to Player direction vector
	*directionVector = math->degreeToDirectionVector(angle);
}

void Player::rotateRight() {
	// sets turn angle
	angle = angle - 0.125;
	// check for overflow
	if (angle <= -360) {
		angle = 0;
	}
	// assign in new angle to Player direction vector
	*directionVector = math->degreeToDirectionVector(angle);
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

void Player::multiplyDirectionVector() {
	*mulitpliedDirectionVector = math->multiplyVector(directionVector, 23);
}

Vector Player::getMultipliedDirectionVector() {
	return *mulitpliedDirectionVector;
}

float Player::getPlayerRadius() {
	return playerRadius;
}

void Player::switchGunType() {
	if (gunType == "normal") {
		gunType = "missile";
	}
	else {
		gunType = "normal";
	}
}

std::string Player::getGunType() {
	return gunType;
}

