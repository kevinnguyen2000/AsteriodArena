#ifndef BULLET
#define BULLET

#include "Types.h"
#include "Vector.h"
#include "Math.h"

class Bullet {
public:
	Bullet(Vector* directionVector, Vector* positionVector);

	void display(std::vector<Bullet> bullets);

	void setDt(float dt);

	void bulletDirection(Bullet bullet);

private:
	Vector* directionVector;
	Vector* positionVector;
	float movementSpeed;
	float dt;
	float angle;
	Math* math;
};

#endif


