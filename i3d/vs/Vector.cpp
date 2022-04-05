#include "Vector.h"

Vector::Vector() {

	this->x = 0;
	this->y = 0;

}

Vector::~Vector() {

}

float Vector::getX() {
	return x;
}

float Vector::getY() {
	return y;
}

void Vector::setX(float x) {
	this->x = x;
}

void Vector::setY(float y) {
	this->y = y;
}