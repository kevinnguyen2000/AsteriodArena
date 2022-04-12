#include "Asteroid.h"

Asteroid::Asteroid() {
	this->directionVector = new Vector();
	this->positionVector = new Vector();
	this->radiusVector = new Vector();
	this->math = new Math();
	this->spawnRadius = 0;
	this->maxAsteroidRadius = 30;
	this->angle = 0;
	this->dt = 0;
	this->movementSpeed = generateMovementSpeed();
	// printf("Movement speed: %f\n", movementSpeed);
	this->appeared = false;
	this->asteroidRadius = 50;
}

// Sets spawn radius from center to corner of screen 
void Asteroid::setSpawnRadius(float x, float y) {
	// set in height and width to calc the radius
	radiusVector->setX(x/2);
	radiusVector->setY(y/2);
	spawnRadius = math->findVectorLength(radiusVector) + maxAsteroidRadius;
	// spawnRadius = 300;
	// printf("Spawn radius: %f \n", spawnRadius);
}

void Asteroid::generateSpawnPoint() {

	// Use radius vector to set min max for x coord number generation
	int maxRandNumber = ceil (spawnRadius * 2);
	int randMinus = spawnRadius;
	// printf("MaxRandNumber: %d\n", maxRandNumber);

	// Generate random x coord 
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> xRange(0, maxRandNumber);
	int asteroidXCoord = float (xRange(rng));

	asteroidXCoord = asteroidXCoord - spawnRadius;
	
	// helper method
	//int asteroidXCoord = spawnRadius;
	
	// Calc y from random x coord
	int asteroidYCoord = math->calculateYFromX(asteroidXCoord, spawnRadius);

	// Set asteroid position vector to coords
	positionVector->setX(asteroidXCoord);
	positionVector->setY(asteroidYCoord);

	// printf("Asteroid pos: %f %f\n", positionVector->getX(), positionVector->getY());
}

void Asteroid::display(std::vector<Asteroid*> asteroids) {
	for (Asteroid* asteroid : asteroids) {

		glPushMatrix();
		glLoadIdentity();

		// tester
		// printf("Asteroid pos: %f %f\n", asteroid.positionVector->getX(), asteroid.positionVector->getY());
		glColor3f(0.5, 0.5, 0.5);
		glTranslatef(asteroid->positionVector->getX(), asteroid->positionVector->getY(), 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glScalef(5.0f, 5.0f, 5.0f);

		glBegin(GL_TRIANGLES);
		glVertex3f(0, 10, 0.0);
		glVertex3f(0, 0, 0.0);
		glVertex3f(7, 7, 0.0);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(0, -10, 0.0);
		glVertex3f(0, 0, 0.0);
		glVertex3f(-7, -7, 0.0);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(-10, 0, 0.0);
		glVertex3f(0, 0, 0.0);
		glVertex3f(-7, -7, 0.0);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(-10, 0, 0.0);
		glVertex3f(0, 0, 0.0);
		glVertex3f(-7, -7, 0.0);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(-10, 0, 0.0);
		glVertex3f(0, 0, 0.0);
		glVertex3f(-7, 7, 0.0);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(-7, 7, 0.0);
		glVertex3f(0, 0, 0.0);
		glVertex3f(0, 10, 0.0);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(10, 0, 0.0);
		glVertex3f(7, 7, 0.0);
		glVertex3f(0, 0, 0.0);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(10, 0, 0.0);
		glVertex3f(7, -7, 0.0);
		glVertex3f(0, 0, 0.0);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(0, 0, 0.0);
		glVertex3f(7, -7, 0.0);
		glVertex3f(0, -10, 0.0);
		glEnd();

		// make outline of spaceship
		glLineWidth(5.0);
		glBegin(GL_LINE_LOOP);
		glColor3f(0.3, 0.15, 0.1);
		glVertex3f(0, 10, 0.0);
		glVertex3f(7, 7, 0.0);
		glVertex3f(10, 0, 0.0);
		glVertex3f(7, -7, 0.0);
		glVertex3f(0, -10, 0.0);
		glVertex3f(-7, -7, 0.0);
		glVertex3f(-10, 0, 0.0);
		glVertex3f(-7, 7, 0.0);
		glEnd();

		glPopMatrix();

		asteroidMovement(*asteroid);
	}
}

void Asteroid::asteroidDirection(Vector* playerVector) {
	*directionVector = math->subtractVector(playerVector, positionVector);
	// tester
	// printf("Asteroid direction vector: %f %f", directionVector->getX(), directionVector->getY());
	float a = math->directionVectorToDegree(directionVector);
	*directionVector = math->degreeToDirectionVector(a);
	// printf("Asteroid direction vector: %f %f", directionVector->getX(), directionVector->getY());
}

void Asteroid::asteroidMovement(Asteroid asteroid) {

	Vector* newCoords = new Vector();
	newCoords->setX(asteroid.positionVector->getX() + asteroid.directionVector->getX() * movementSpeed * dt);
	newCoords->setY(asteroid.positionVector->getY() + asteroid.directionVector->getY() * movementSpeed * dt);

	asteroid.positionVector->setX(newCoords->getX());
	asteroid.positionVector->setY(newCoords->getY());
}

void Asteroid::setDt(float dt) {
	this->dt = dt;
}

float Asteroid::generateMovementSpeed() {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> movementRange(125, 225); 

	return float (movementRange(rng));
}

void Asteroid::setAppearedTrue() {
	this->appeared = true;
}

bool Asteroid::getAppeared() {
	return appeared;
}

Vector Asteroid::getPositionVector() {
	return *positionVector;
}

bool Asteroid::checkBulletCollision(float bulletX, float bulletY) {
	float distance = sqrt((positionVector->getX() - bulletX) * (positionVector->getX() - bulletX) + (positionVector->getY() - bulletY) * (positionVector->getY() - bulletY));
	printf("distance: %f\n", distance);
	if (maxAsteroidRadius >= distance) {
		return true;
	}
	else {
		return false;
	}
}