#include "Asteroid.h"

Asteroid::Asteroid() {
	this->directionVector = new Vector();
	this->positionVector = new Vector();
	this->radiusVector = new Vector();
	this->math = new Math();
	this->spawnRadius = 0;
	this->maxAsteroidRadius = 0;
	this->asteriodRadius = 0;
	this->angle = 0;
	this->dt = 0;
	this->movementSpeed = generateMovementSpeed();
	this->appeared = false;
	this->asteroidScale = 5;
	this->maxVertexLength = 0;
	this->minVertexLength = 0;
	generateAsteroidShape();
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

/*
void Asteroid::generateAsteroidSize() {
	// Generate max size
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> sizeRange(4, 16);
	maxVertexLength = float (sizeRange(rng));
	// printf("Max vertex length: %f", maxVertexLength);
	// maxVertexLength = 10;

	// subtract to get min size for vertex for different sizes
	if (maxVertexLength >= 4 and maxVertexLength < 8) {
		minVertexLength = maxVertexLength - 1;
	}
	if (maxVertexLength >= 8 and maxVertexLength < 12) {
		minVertexLength = maxVertexLength - 3;
	}
	if (maxVertexLength >= 12 and maxVertexLength <= 16) {
		minVertexLength = maxVertexLength - 4;
	}

	// set max asteroid radius
	maxAsteroidRadius = maxVertexLength * asteroidScale;
}
*/

void Asteroid::generateAsteroidShape() {
	// Determine if small, medium or large asteroid
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> sizeRange(0, 2);
	int size = sizeRange(rng);
	printf("size: %d", size);

	for (int i = 0; i < 360; i += 15) {
		if (size == 0) {
			std::uniform_int_distribution<std::mt19937::result_type> sizeSmall(4, 6);
			asteriodRadius = sizeSmall(rng);
			Vector currentDirection = math->degreeToDirectionVector(i);
			currentDirection.setX(currentDirection.getX() * asteriodRadius);
			currentDirection.setY(currentDirection.getY() * asteriodRadius);
			vertices.push_back(currentDirection);

		}
		if (size == 1) {
			std::uniform_int_distribution<std::mt19937::result_type> sizeMedium(9, 11);
			asteriodRadius = sizeMedium(rng);
			Vector currentDirection = math->degreeToDirectionVector(i);
			currentDirection.setX(currentDirection.getX() * asteriodRadius);
			currentDirection.setY(currentDirection.getY() * asteriodRadius);
			vertices.push_back(currentDirection);
		}
		if (size == 2) {
			std::uniform_int_distribution<std::mt19937::result_type> sizeLarge(14, 16);
			asteriodRadius = sizeLarge(rng);
			Vector currentDirection = math->degreeToDirectionVector(i);
			currentDirection.setX(currentDirection.getX() * asteriodRadius);
			currentDirection.setY(currentDirection.getY() * asteriodRadius);
			vertices.push_back(currentDirection);
		}
	}

	// set max asteroid radius
	maxAsteroidRadius = asteriodRadius * asteroidScale;
}

void Asteroid::display(std::vector<Asteroid*> asteroids) {
	for (Asteroid* asteroid : asteroids) {

		glPushMatrix();
		glLoadIdentity();

		glColor3f(0.5, 0.5, 0.5);
		glTranslatef(asteroid->positionVector->getX(), asteroid->positionVector->getY(), 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glScalef(asteroid->asteroidScale, asteroidScale, asteroidScale);

		glBegin(GL_POLYGON);
		for (Vector vertex : asteroid->vertices) {
			glVertex3f(vertex.getX(), vertex.getY(), 0.0);
		}

		glEnd();

		// make outline of asteroid
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
		glColor3f(0.3, 0.15, 0.1);
		for (Vector vertex : asteroid->vertices) {
			glVertex3f(vertex.getX(), vertex.getY(), 0.0);
		}
		
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

bool Asteroid::checkCollision(float xCoord, float yCoord, float radius) {
	float distance = sqrt(((positionVector->getX() - xCoord) * (positionVector->getX() - xCoord) + (positionVector->getY() - yCoord) * (positionVector->getY() - yCoord)));
	//printf("Asteroid position: (%f) (%f)\n", positionVector->getX(), positionVector->getY());
	//printf("Bullet position: (%f) (%f)\n", xCoord, yCoord);
	//printf("distance: %f\n", distance);
	// printf("Max asteroid radius: %f", maxAsteroidRadius);
	if (maxAsteroidRadius + radius >= distance) {
		return true;
	}
	else {
		return false;
	}
}