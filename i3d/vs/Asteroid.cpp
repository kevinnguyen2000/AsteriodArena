#include "Asteroid.h"

Asteroid::Asteroid() {
	this->directionVector = new Vector();
	this->positionVector = new Vector();
	this->radiusVector = new Vector();
	this->math = new Math();
	this->spawnRadius = 0;
	this->maxAsteroidRadius = 100;
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
	int maxRandNumber = radiusVector->getX() * 2;
	int randMinus = radiusVector->getX();

	// Generate random x coord 
	srand(time(0));
	for (int i = 0; i < 10; i++) {
		int asteroidXCoord = rand() % maxRandNumber;
		asteroidXCoord = asteroidXCoord - randMinus;
		printf("Asteriod x coord: %d\n", asteroidXCoord);
	}

	// Calc y from random x coord

	// Set asteroid position vector to coords
}