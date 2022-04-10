#include "Asteriod.h"

Asteriod::Asteriod() {
	this->directionVector = new Vector();
	this->positionVector = new Vector();
	this->radiusVector = new Vector();
	this->math = new Math();
	this->spawnRadius = 0;
	this->maxAsteriodRadius = 100;
}

// Sets spawn radius from center to corner of screen 
void Asteriod::setSpawnRadius(float x, float y) {
	radiusVector->setX(x/2);
	radiusVector->setY(y/2);
	spawnRadius = math->findVectorLength(radiusVector) + maxAsteriodRadius;
	//printf("Spawn radius: %f \n", spawnRadius);
}