#ifndef PLAYER
#define PLAYER

#include "Types.h"
#include "Vector.h"

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

	// private class variables
private:
	Vector* directionVector;
	Vector* positionVector;
	int angle;
	//std::vector<float> directionVector;
	//std::vector<float> positonVector;
};

#endif
