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

	void setX(float x);
	void setY(float y);

	// private class variables
	private:
		float x;
		float y;
};

#endif