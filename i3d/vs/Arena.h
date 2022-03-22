#ifndef ARENA
#define ARENA

#include "Types.h"

class Arena {
public:
	// Constructor and Deconstructor 
	Arena(int width, int height);
	~Arena();

	// Copy constrcutor
	Arena(Arena& other);

	// Displays Arena
	void display();

	// private class variables
	private: 
		int width;
		int height;
};

#endif


