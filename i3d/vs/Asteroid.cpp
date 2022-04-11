#include "Asteroid.h"

Asteroid::Asteroid() {
	this->directionVector = new Vector();
	this->positionVector = new Vector();
	this->radiusVector = new Vector();
	this->math = new Math();
	this->spawnRadius = 0;
	this->maxAsteroidRadius = 50;
	this->angle = 0;
	this->dt = 0;
	this->movementSpeed = 0;
}

// Sets spawn radius from center to corner of screen 
void Asteroid::setSpawnRadius(float x, float y) {
	// set in height and width to calc the radius
	radiusVector->setX(x/2);
	radiusVector->setY(y/2);
	spawnRadius = math->findVectorLength(radiusVector) + maxAsteroidRadius;
	printf("Spawn radius: %f \n", spawnRadius);

}

void Asteroid::generateSpawnPoint() {
	// Use radius vector to set min max for x coord number generation
	int maxRandNumber = ceil (spawnRadius * 2);
	int randMinus = spawnRadius;
	printf("MaxRandNumber: %d\n", maxRandNumber);

	// Generate random x coord 
	srand((unsigned int)time(NULL));
	int asteroidXCoord = rand() % maxRandNumber;
	asteroidXCoord = asteroidXCoord - randMinus;
	
	// helper method
	//int asteroidXCoord = spawnRadius;
	
	// Calc y from random x coord
	int asteroidYCoord = math->calculateYFromX(asteroidXCoord, spawnRadius);

	// Set asteroid position vector to coords
	positionVector->setX(asteroidXCoord);
	positionVector->setY(asteroidYCoord);

	printf("Asteroid pos: %f %f\n", positionVector->getX(), positionVector->getY());
}

void Asteroid::display(std::vector<Asteroid> asteroids) {
	for (Asteroid asteroid : asteroids) {

		glPushMatrix();
		glLoadIdentity();

		// tester
		// printf("Asteroid pos: %f %f\n", asteroid.positionVector->getX(), asteroid.positionVector->getY());
		glColor3f(0.5, 0.5, 0.5);
		glTranslatef(asteroid.positionVector->getX(), asteroid.positionVector->getY(), 0.0f);
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

		glPopMatrix();
	}
}

void Asteroid::asteroidDirection(Vector* playerVector) {
	*directionVector = math->subtractVector(playerVector, positionVector);
	// tester
	printf("Asteroid direction vector: %f %f", directionVector->getX(), directionVector->getY());
}