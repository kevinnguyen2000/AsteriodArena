#include "Arena.h"

Arena::Arena() {

}

void Arena::display() {

	// clears previous renders if existed
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	// One pixel stars
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	glVertex3f(100, 100, -0.75);
	glVertex3f(-450, -300, -0.75);
	glEnd();

	// Larger star
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(5, -5, -0.5);
	glVertex3f(-5, -5, -0.5);
	glVertex3f(-5, 5, -0.5);
	glVertex3f(5, 5, -0.5);
	glEnd();

	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
}
