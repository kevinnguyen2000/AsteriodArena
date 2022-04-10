#ifndef ASTERIOD
#define ASTERIOD

#include "Types.h"
#include "Vector.h"
#include "Math.h"

class Asteriod {
public:
	Asteriod();

	void setSpawnRadius(float x, float y);

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
	float maxAsteriodRadius;
};

#endif
