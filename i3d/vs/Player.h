#ifndef PLAYER
#define PLAYER

#include "Types.h"

class Player {
public:
	// Constructor and Deconstructor
	Player();
	~Player();

	// Displays player
	void display();

	// Set player starting postion
	void setPlayerInitalPosition(int initalX, int intialY);

	// private class variables
private:
	int intialX;
	int initalY;
};

#endif
