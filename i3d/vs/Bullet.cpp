#include "Bullet.h"

Bullet::Bullet(Vector* directionVector, Vector* positionVector) {
	this->directionVector = directionVector;
	this->positionVector = positionVector;
	this->movementSpeed = 200;
	this->dt = 0;
	this->angle = 0;
	this->math = new Math();
}

void Bullet::display(std::vector<Bullet> bullets) {
	
	Bullet bullet = bullets.back();

	glPushMatrix();
	glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);
	glPointSize(2.0);
	glTranslatef(bullet.positionVector->getX(), bullet.positionVector->getY(), 0.0f);
	glRotatef(bullet.angle, 0.0f, 0.0f, 1.0f);
	glScalef(1.5f, 1.5f, 1.5f);

	glBegin(GL_POINTS);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glPopMatrix();
}

void Bullet::setDt(float dt) {
	this->dt = dt;
}

void Bullet::bulletDirection(Bullet bullet) {
	// Bullet direction
	Vector* newCoords = new Vector();
	newCoords->setX(bullet.positionVector->getX() + bullet.directionVector->getX() * movementSpeed * dt);
	newCoords->setY(bullet.positionVector->getY() + bullet.directionVector->getY() * movementSpeed * dt);

	bullet.positionVector->setX(newCoords->getX());
	bullet.positionVector->setY(newCoords->getY());
}
