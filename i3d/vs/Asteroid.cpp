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
	int maxRandNumber = spawnRadius * 2;
	int randMinus = spawnRadius;
	printf("MaxRandNumber: %d\n", maxRandNumber);

	// Generate random x coord 
	srand(time(0));
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