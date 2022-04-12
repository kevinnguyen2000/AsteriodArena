#ifndef BULLET
#define BULLET

#include "Types.h"
#include "Vector.h"
#include "Math.h"

class Bullet {
public:
	Bullet();

	void display(std::vector<Bullet*> bullets);

	void setDt(float dt);

	void setBulletPositionVector(float x, float y);
	void setDirectionVector(float x, float y);

	void bulletDirection(Bullet bullet);

	Vector getPositionVector();

private:
	Vector* directionVector;
	Vector* positionVector;
	float movementSpeed;
	float dt;
	float angle;
	Math* math;
};

#endif


