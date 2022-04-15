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
	this->rotationSpeed = 0;
	this->rotateClockWise = false;
	this->hitPoints = 0;
	
	generateAsteroidShape();
	generateRotation();
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

void Asteroid::generateAsteroidShape() {
	// Determine if small, medium or large asteroid
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> sizeRange(0, 2);
	int size = sizeRange(rng);

	for (int i = 0; i < 360; i += 30) {
		if (size == 0) {
			std::uniform_int_distribution<std::mt19937::result_type> sizeSmall(4, 6);
			asteriodRadius = sizeSmall(rng);
			Vector currentDirection = math->degreeToDirectionVector(i);
			currentDirection.setX(currentDirection.getX() * asteriodRadius);
			currentDirection.setY(currentDirection.getY() * asteriodRadius);
			vertices.push_back(currentDirection);
			hitPoints = 2;

		}
		if (size == 1) {
			std::uniform_int_distribution<std::mt19937::result_type> sizeMedium(9, 11);
			asteriodRadius = sizeMedium(rng);
			Vector currentDirection = math->degreeToDirectionVector(i);
			currentDirection.setX(currentDirection.getX() * asteriodRadius);
			currentDirection.setY(currentDirection.getY() * asteriodRadius);
			vertices.push_back(currentDirection);
			hitPoints = 3;
		}
		if (size == 2) {
			std::uniform_int_distribution<std::mt19937::result_type> sizeLarge(14, 16);
			asteriodRadius = sizeLarge(rng);
			Vector currentDirection = math->degreeToDirectionVector(i);
			currentDirection.setX(currentDirection.getX() * asteriodRadius);
			currentDirection.setY(currentDirection.getY() * asteriodRadius);
			vertices.push_back(currentDirection);
			hitPoints = 4;
		}
	}
	// printf("HP: %d", hitPoints);

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

		// make outline of asteroid based on hitpoints
		if (asteroid->hitPoints == 4) {
			glColor3f(0.3, 0.15, 0.1);
		}
		if (asteroid->hitPoints == 3) {
			glColor3f(0.55, 0.47, 0.14);
		}
		if (asteroid->hitPoints == 2) {
			glColor3f(0.6, 0.8, 0.2);
		}
		if (asteroid->hitPoints == 1) {
			glColor3f(1.0, 0.1, 0.1);
		}
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
		for (Vector vertex : asteroid->vertices) {
			glVertex3f(vertex.getX(), vertex.getY(), 0.0);
		}
		
		glEnd();
		glPopMatrix();

		asteroidMovement(*asteroid);
		asteroidRotate(*asteroid);
	}
}

void Asteroid::asteroidRotate(Asteroid asteroid) {
	// check overflow
	if (angle >= 360 or angle <= -360) {
		angle = 0;
	}
	if (rotateClockWise == false) {
		asteroid.rotationSpeed = asteroid.rotationSpeed / 50;
		angle = angle + asteroid.rotationSpeed;
		//printf("Asteroid angle: %f\n", angle);
		//printf("Rotation speed: %f\n", asteroid.rotationSpeed);
	}
	else {
		asteroid.rotationSpeed = asteroid.rotationSpeed / 50;
		angle = angle - asteroid.rotationSpeed;
		//printf("Rotation angle: %f\n", angle);
		//printf("Rotation speed: %f\n", asteroid.rotationSpeed);
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

void Asteroid::generateRotation() {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> rotationSpeed(1, 2);

	this->rotationSpeed = float (rotationSpeed(rng));
	
	std::uniform_int_distribution<std::mt19937::result_type> rotation(0, 1);
	if (rotation(rng) == 1) {
		this->rotateClockWise = true;
	}
}

void Asteroid::decreaseHP(float damage) {
	hitPoints = hitPoints - damage;
}

int Asteroid::getHP() {
	return hitPoints;
}