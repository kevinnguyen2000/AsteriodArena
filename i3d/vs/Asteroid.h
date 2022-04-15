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

	bool checkCollision(float xCoord, float yCoord, float radius);

	void generateAsteroidShape();

	void generateRotation();
	void asteroidRotate(Asteroid asteroid);

	void decreaseHP(float damage);
	int getHP();

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
	float asteriodRadius;
	bool appeared;
	float asteroidScale;
	float maxVertexLength;
	float minVertexLength;
	std::vector<Vector> vertices;
	double rotationSpeed;
	bool rotateClockWise;
	int hitPoints;
};

#endif
