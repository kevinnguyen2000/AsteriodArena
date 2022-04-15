#include "Missile.h";

Missile::Missile() {
	this->positionVector = new Vector();
	this->directionVector = new Vector();
	this->math = new Math();
	this->angle = 0;
	this->dt = 0;
	this->movementSpeed = 300;
	this->scale = 2;
	this->radius = 12;
}

void Missile::setDt(float dt) {
	this->dt = dt;
}

void Missile::display(std::vector<Missile*> missiles) {
	for (Missile* missile : missiles) {
		glPushMatrix();
		glLoadIdentity();

		//printf("First bullet: (%f) (%f) \n", bullet.positionVector->getX(), bullet.positionVector->getY());

		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(missile->positionVector->getX(), missile->positionVector->getY(), 0.0f);
		glRotatef(missile->angle, 0.0f, 0.0f, 1.0f);
		glScalef(scale, scale, scale);

		glBegin(GL_POLYGON);
		// Body of missile
		glVertex3f(-5, 1, 0.0);
		glVertex3f(3, 1, 0.0);
		glVertex3f(6, 0, 0.0);
		glVertex3f(3, -1, 0.0);
		glVertex3f(-5, -1, 0.0);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		// Fins of missile
		glBegin(GL_TRIANGLES);
		glVertex3f(-5, 1, 0.0);
		glVertex3f(-5, 3, 0.0);
		glVertex3f(-3, 1, 0.0);

		glVertex3f(-5, -1, 0.0);
		glVertex3f(-5, -3, 0.0);
		glVertex3f(-3, -1, 0.0);

		glVertex3f(0, -1, 0.0);
		glVertex3f(0, -2, 0.0);
		glVertex3f(1, -1, 0.0);

		glVertex3f(0, 1, 0.0);
		glVertex3f(0, 2, 0.0);
		glVertex3f(1, 1, 0.0);
		glEnd();

		glPopMatrix();

		missileDirection(*missile);

	}
}

void Missile::missileDirection(Missile missile) {
	// Missile direction
	Vector* newCoords = new Vector();
	newCoords->setX(missile.positionVector->getX() + missile.directionVector->getX() * movementSpeed * dt);
	newCoords->setY(missile.positionVector->getY() + missile.directionVector->getY() * movementSpeed * dt);

	missile.positionVector->setX(newCoords->getX());
	missile.positionVector->setY(newCoords->getY());
}

void Missile::missileDirectionToAsteroid(Vector* asteroid) {
	*directionVector = math->subtractVector(asteroid, positionVector);
	// tester
	// printf("Asteroid direction vector: %f %f", directionVector->getX(), directionVector->getY());
	float a = math->directionVectorToDegree(directionVector);
	angle = a;
	// printf("Angle: %f", a);
	*directionVector = math->degreeToDirectionVector(a);
}

void Missile::setMissilePositionVector(float x, float y) {
	this->positionVector->setX(x);
	this->positionVector->setY(y);
}

void Missile::setDirectionVector(float x, float y) {
	this->directionVector->setX(x);
	this->directionVector->setY(y);
}

float Missile::checkDistance(float xCoord, float yCoord, float radius) {
	float distance = sqrt(((positionVector->getX() - xCoord) * (positionVector->getX() - xCoord) + (positionVector->getY() - yCoord) * (positionVector->getY() - yCoord)));
	return distance;
}

float Missile::getRadius() {
	return radius;
}

Vector Missile::getPositionVector() {
	return *positionVector;
}