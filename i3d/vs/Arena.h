#ifndef ARENA
#define ARENA

#include "Types.h"
#include "Vector.h"

class Arena {
public:
	// Constructor and Deconstructor 
	Arena();
	~Arena();

	// Displays arena
	void display();

	// Set arena height and width
	void setArena(int width, int height);

	// Get arena height and width
	int getArenaHeight();
	int getArenaWidth();

	// Set circle world position vector
	void setCircleWorldPositionVector(Vector* positonVector);

	// Check for wall collision
	void checkWallCollision();

	// Get and set collision
	bool getCollision();
	void setCollisionFalse();

	// Private class variables
	private: 
		int width;
		int height;
		Vector* circleWorldPosition;
		Vector* arenaSize;
		float circleRadius;
		float leftWallColour, rightWallColour, topWallColour, bottomWallColour;
		bool collision;
};

#endif


