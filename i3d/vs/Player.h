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

	// Reset player position
	void resetPlayer();

	// private class variables
private:
	Vector* directionVector;
	Vector* positionVector;
	float angle;
	float movementSpeed;
	float dt;
	Math* math;
};

#endif
