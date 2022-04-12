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

Vector Math::subtractVector(Vector *a, Vector *b) {
	Vector* subtractedVector = new Vector();
	subtractedVector->setX(a->getX() - b->getX());
	subtractedVector->setY(a->getY() - b->getY());

	return *subtractedVector;
}

Vector Math::addVector(Vector* a, Vector* b) {
	Vector* addedVector = new Vector();
	addedVector->setX(a->getX() + b->getX());
	addedVector->setY(a->getY() + b->getY());

	return *addedVector;
}

Vector Math::multiplyVector(Vector* a, float s) {
	Vector* multipliedVector = new Vector();
	multipliedVector->setX(a->getX() * s);
	multipliedVector->setY(a->getY() * s);

	return *multipliedVector;
}

float Math::findVectorLength(Vector* a) {
	float length = sqrt(a->getX() * a->getX() + a->getY() * a->getY());
	
	return length;
}

float Math::dotProduct(Vector* a, Vector* b) {
	float dotProduct = a->getX() * b->getX() + a->getY() * b->getY();

	return dotProduct;
}

float Math::angleBetweenVectors(Vector* a, Vector* b) {
	float degrees = acos(dotProduct(a, b) / (findVectorLength(a) * findVectorLength(b)));

	return degrees;
}

int Math::calculateYFromX(int x, float radius) {
	int yCoord = radius * radius - x * x;
	yCoord = sqrt(yCoord);
	// Generate either minus or positive y Coord
	srand(time(0));
	int sign = rand() % 2;
	// printf("sign: %d\n", sign);
	if (sign == 0) {
		yCoord = -yCoord;
	}
	//printf("YCoord: %d", yCoord);
	return yCoord;
}

float Math::directionVectorToDegree(Vector* a) {
	float angle = atan2(a->getY(), a->getX()) * 180/PI;
	return angle;
}