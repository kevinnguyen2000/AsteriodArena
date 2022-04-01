#ifndef VECTOR
#define VECTOR

#include "Types.h"

class Vector {
public:
	// Constructor / Deconstructor
	Vector();
	~Vector();

	float getX();
	float getY();

	// private class variables
	private:
		float x;
		float y;
};

#endif