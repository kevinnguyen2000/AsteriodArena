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

	void display(std::vector<Asteroid*> asteroids);

	void asteroidDirection(Vector* playerVector);

	void asteroidMovement(Asteroid asteroid);

	void setDt(float dt);

	float generateMovementSpeed();

	bool getAppeared();
	void setAppearedTrue();

	Vector getPositionVector();

	bool checkCollision(float xCoord, float yCoord);

private:
	Vector* radiusVector;
	Vector* directionVector;
	Vector* positionVector;
	float movementSpeed;
	float dt;
	float angle;
	Math* math;
	float spawnRadius;
	float maxAsteroidRadius;
	bool appeared;
	float asteroidRadius;
};

#endif
