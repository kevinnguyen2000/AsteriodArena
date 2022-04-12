#ifndef PLAYER
#define PLAYER

#include "Types.h"
#include "Vector.h"
#include "Math.h"

class Player {
public:
	// Constructor and Deconstructor
	Player();
	~Player();

	// Displays player
	void display();

	// Moves player foward
	void moveFoward();

	// Rotate player left
	void rotateLeft();

	// Rotate player right
	void rotateRight();

	// Set dt
	void setDt(float dt);

	Vector getPositionVector();
	Vector getDirectionVector();
	Vector getMultipliedDirectionVector();

	// Reset player position
	void resetPlayer();

	void multiplyDirectionVector();

	// private class variables
private:
	Vector* directionVector;
	Vector* mulitpliedDirectionVector;
	Vector* positionVector;
	float angle;
	float movementSpeed;
	float dt;
	Math* math;
	float maxSpeed;
};

#endif
