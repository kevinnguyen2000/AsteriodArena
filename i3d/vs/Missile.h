#ifndef MISSILE
#define MISSILE

#include "Types.h"
#include "Vector.h"
#include "Math.h"

class Missile {
public:
	Missile();

	void setDt(float dt);

	void display(std::vector<Missile*> missiles);

	void setMissilePositionVector(float x, float y);
	void setDirectionVector(float x, float y);

private:
	Vector* directionVector;
	Vector* positionVector;
	float movementSpeed;
	float dt;
	float angle;
	Math* math;
};

#endif