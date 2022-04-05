#ifndef MATH
#define MATH

#include "Types.h"
#include "Vector.h"

class Math {
public:
	// Convert angle into direction vector
	Vector degreeToDirectionVector(float degrees);

	Vector subtractVector(Vector *a, Vector *b);

	// private class variables
	private:
		float PI = 3.14159265359;
};

#endif
