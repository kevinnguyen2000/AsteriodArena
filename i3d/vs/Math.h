#ifndef MATH
#define MATH

#include "Types.h"
#include "Vector.h"

class Math {
public:
	// Convert angle into direction vector
	Vector degreeToDirectionVector(float degrees);

	Vector subtractVector(Vector *a, Vector *b);

	Vector addVector(Vector* a, Vector* b);

	Vector multiplyVector(Vector* a, float s);

	float findVectorLength(Vector* a);

	float dotProduct(Vector* a, Vector* b);

	float angleBetweenVectors(Vector* a, Vector* b);

	int calculateYFromX(int x, float radius);

	float directionVectorToDegree(Vector* a);

	// private class variables
	private:
		float PI = 3.14159265359;
};

#endif
