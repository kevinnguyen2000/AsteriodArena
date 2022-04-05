#include "Math.h"

Vector Math::degreeToDirectionVector(float degrees) {
	// Convert degrees to radians
	float radians = degrees * (PI / 180);
	// Convert Radians to direction vector
	float x = cos(radians);
	float y = sin(radians);
	Vector* directionVector = new Vector;
	directionVector->setX(x);
	directionVector->setY(y);
	// tester
	/*
	printf("Degrees: %f", degrees);
	printf( "X and Y: (%f, %f)\n", x, y);
	*/

	return *directionVector;
}