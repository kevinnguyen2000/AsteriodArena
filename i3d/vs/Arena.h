#ifndef ARENA
#define ARENA

#include "Types.h"

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

	// private class variables
	private: 
		int width;
		int height;
};

#endif


