#include "../vs/Arena.h"
#include "../vs/Player.h"
#include "../vs/Types.h"
#include "../vs/Bullet.h"

// Create arena object
Arena* arena = new Arena();

// Create player object
Player* player = new Player();

// Vector for player positon
Vector* playerPosition = new Vector();
// Vector for player direction
Vector* playerDirection = new Vector();

// Vector of bullets
std::vector<Bullet> bullets;
Bullet* bullet = new Bullet(0, 0);
Vector* bulletPosition = new Vector();
Vector* bulletDirection = new Vector();

float g_last_time = 0.0;

void reset_game() {
	// Set collision back to false
	arena->setCollisionFalse();
	// Set player position back to starting state
	player->resetPlayer();
}

void display()
{
	// clears previous renders if existed
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_DEPTH_TEST);

	arena->display();
	player->display();
	if (bullets.size() > 0) {
		bullet->display(bullets);
	}
	
	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
	
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
	case 'w':
		player->moveFoward();
		// Check wall collision
		*playerPosition = player->getPositionVector();
		arena->setCircleWorldPositionVector(playerPosition);
		arena->checkWallCollision();
		if (arena->getCollision() == true) {
			reset_game();
		}
		break;
	case 'a':
		player->rotateLeft();
		break;
	case 'd':
		player->rotateRight();
		break;
	default:
		break;
	}
}

void on_mouse_button(int button, int state, int x, int y)
{
	*bulletPosition = player->getPositionVector();
	*bulletDirection = player->getDirectionVector();

	// Make new bullet on left click press
	Bullet* bullet = new Bullet(bulletDirection, bulletPosition);
	// add Bullet to bullet array
	bullets.push_back(*bullet);
}

void update_game_state(float dt) {
	// tester
	// printf("DT: (%f)\n", dt);
	player->setDt(dt);
	bullet->setDt(dt);
}

// function for calculating dt , from lec 2
float calc_dt() {
	float cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	float dt = cur_time - g_last_time;
	g_last_time = cur_time;

	//printf("DT, CT, LAST_T: (%f)(%f)(%f)\n", dt, cur_time, g_last_time);
	return dt;
}

void on_idle()
{
	float dt = calc_dt();
	update_game_state(dt);
	glutPostRedisplay();
}

void run_app()
{
	glutMainLoop();
}

// Tute 3 code for reshaping
void on_reshape(int w, int h)
{
	fprintf(stderr, "testing dynamic arena (%d, %d)\n", w, h);
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1.0, 1.0);

	arena->setArena(w, h);
}

void init(int* argcp, char** argv)
{
	glutInit(argcp, argv);
	// initialise rgb mode, double buffer and depth buffering.
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Asteriod Arena");
	// makes window full screen.
	glutFullScreen();

	glutReshapeFunc(on_reshape);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(on_mouse_button);

	// idle function
	glutIdleFunc(on_idle);
}

int main(int argc, char** argv)
{
	init(&argc, argv);
	run_app();
	return EXIT_SUCCESS;
}