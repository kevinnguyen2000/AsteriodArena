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

	// private class variables
private:
	Vector* positonVector;
	Vector* directionVector;
};

#endif
