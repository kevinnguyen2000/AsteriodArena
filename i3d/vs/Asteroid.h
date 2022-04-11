#ifndef ASTEROID
#define ASTEROID

#include "Types.h"
#include "Vector.h"
#include "Math.h"

class Asteroid {
public:
	Asteroid();

	void setSpawnRadius(float x, float y);

	void generateSpawnPoint();

	void display(std::vector<Asteroid> asteroids);

private:
	Vector* radiusVector;
	Vector* directionVector;
	Vector* positionVector;
	float movementSpeed;
	float dt;
	float angle;
	Math* math;
	// radius is from center to corner of screen
	float spawnRadius;
	float maxAsteroidRadius;
};

#endif
