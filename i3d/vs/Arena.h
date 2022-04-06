#ifndef ARENA
#define ARENA

#include "Types.h"
#include "Vector.h"

class Arena {
public:
	// Constructor and Deconstructor 
	Arena();
	~Arena();

	// Copy constrcutor
	Arena(Arena& other);

	// Displays arena
	void display();

	// Set arena height and width
	void setArena(int width, int height);

	// Set circle world position vector
	void setCircleWorldPositionVector(Vector* positonVector);

	// Private class variables
	private: 
		int width;
		int height;
		Vector* circleWorldPosition;
		Vector* arenaSize;
		float circleRadius;
};

#endif


