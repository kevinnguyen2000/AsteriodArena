#include "../vs/Arena.h"
#include "../vs/Types.h"

void display(void)
{
	// Make arena object and call display it
	Arena* arena = new Arena();
	arena->display();
	
}

/* You can ignore this for now, it just lets you exit when you press 'q' or ESC */
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	case 'q':
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}
}

// Tute 3 code for reshaping
void on_reshape(int w, int h)
{
	fprintf(stderr, "on_reshape(%d, %d)\n", w, h);
	glViewport(w/2, h/2, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, w, -1.0, h, -1.0, 1.0);
}

void init(int* argcp, char** argv)
{
	/* In this program these OpenGL calls only need to be done once,
	  but normally they would go elsewhere, e.g. display */

	glutInit(argcp, argv);
	// initialise rgb mode, double buffer and depth buffering.
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Asteriod Arena");
	// makes window full screen.
	glutFullScreen();

	glutReshapeFunc(on_reshape);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
}

int main(int argc, char** argv)
{
	init(&argc, argv);
	glutMainLoop();
	return EXIT_SUCCESS;
}
