#include "Bullet.h"

Bullet::Bullet() {
	this->directionVector = new Vector();
	this->positionVector = new Vector();
	this->movementSpeed = 350;
	this->dt = 0;
	this->angle = 0;
	this->math = new Math();
}

void Bullet::display(std::vector<Bullet> bullets) {

	glPushMatrix();
	glLoadIdentity();

    Bullet bullet = bullets.back();
	
	//for (Bullet bullet : bullets) {

		//printf("First bullet: (%f) (%f) \n", bullet.positionVector->getX(), bullet.positionVector->getY());

		glColor3f(1.0, 1.0, 1.0);
		glPointSize(2.0);
		glTranslatef(bullet.positionVector->getX(), bullet.positionVector->getY(), 0.0f);
		glRotatef(bullet.angle, 0.0f, 0.0f, 1.0f);
		glScalef(0.0f, 0.0f, 0.0f);

		glBegin(GL_POINTS);
		glVertex3f(0.0, 0.0, 0.0);
		glEnd();

		//printf("Bullet: (%f) (%f) \n", bullet.positionVector->getX(), bullet.positionVector->getY());
	//}

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

Vector Bullet::getPositionVector() {
	return *positionVector;
}

/*
void Bullet::setVectors(Vector positionVector, Vector directionVector) {
	this->positionVector = positionVector;
	this->directionVector = directionVector;
}
*/

void Bullet::setBulletPositionVector(float x, float y) {
	this->positionVector->setX(x);
	this->positionVector->setY(y);
}
