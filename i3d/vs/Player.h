#ifndef PLAYER
#define PLAYER

#include "Types.h"
#include "Vector.h"
#include "Math.h"

class Player {
public:
	// Constructor and Deconstructor
	Player();
	~Player();

	// Displays player
	void display();

	// Moves player foward
	void moveFoward();
	void slowDown();

	// Rotate player left
	void rotateLeft();

	// Rotate player right
	void rotateRight();

	// Set dt
	void setDt(float dt);

	Vector getPositionVector();
	Vector getDirectionVector();
	Vector getMultipliedDirectionVector();

	// Reset player position
	void resetPlayer();

	void multiplyDirectionVector();

	float getPlayerRadius();

	void switchGunType();
	std::string getGunType();

	// private class variables
private:
	Vector* directionVector;
	Vector* mulitpliedDirectionVector;
	Vector* positionVector;
	float angle;
	float movementSpeed;
	float dt;
	Math* math;
	float maxSpeed;
	float playerRadius;
	std::string gunType;
};

#endif
