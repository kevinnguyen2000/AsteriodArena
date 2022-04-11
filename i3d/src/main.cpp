#include "../vs/Arena.h"
#include "../vs/Player.h"
#include "../vs/Types.h"
#include "../vs/Bullet.h"
#include "../vs/Asteroid.h"

// Create arena object
Arena* arena = new Arena();

// Create player object
Player* player = new Player();

// Vector for player positon
Vector* playerPosition = new Vector();
// Vector for player direction
Vector* playerDirection = new Vector();

// Vector of bullets
std::vector<Bullet>* bullets = new std::vector<Bullet>;
Bullet* bullet = new Bullet();

float g_last_time = 0.0;

float maxShipFireRate = 0.25;
float shipFireRateCounter = 0;

// Vector of asteriods
std::vector<Asteroid>* asteroids = new std::vector<Asteroid>;
Asteroid* asteroid = new Asteroid();

float maxAsteroidRate = 4;
float asteroidSpawnRateCounter = 0;

float width, height = 0;

void reset_game() {
	// Set collision back to false
	arena->setCollisionFalse();
	// Set player position back to starting state
	player->resetPlayer();
	// clears all bullets on screen
	bullets->clear();
}

void display()
{
	// clears previous renders if existed
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_DEPTH_TEST);

	arena->display();
	player->display();
	if (bullets->size() > 0) {
		bullet->display(*bullets);
	}
	if (asteroids->size() > 0) {
		asteroid->display(*asteroids);
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

void checkAsteroidSpawn() {
	if (asteroidSpawnRateCounter >= maxAsteroidRate) {
		// Make Asteroid
		Asteroid* newAsteroid = new Asteroid();
		// set spawn radius
		newAsteroid->setSpawnRadius(width, height);
		// Generate spawn position for new asteroid
		newAsteroid->generateSpawnPoint();
		// Calc direction of asteroid
		*playerPosition = player->getPositionVector();
		newAsteroid->asteroidDirection(playerPosition);
		// Add new Asteroid to asteroids vector
		asteroids->push_back(*newAsteroid);
		
		// Set asteroid counter back to zero
		asteroidSpawnRateCounter = 0;
	}
}

void checkBulletBounds() {
	auto it = bullets->begin();
	while (it != bullets->end()) {
		// checks left wall
		if (it->getPositionVector().getX() < -arena->getArenaWidth() / 2) {
			it = bullets->erase(it);
		}
		// checks top wall
		if (it->getPositionVector().getY() > arena->getArenaHeight() /2) {
			it = bullets->erase(it);
		}
		// checks right wall
		if (it->getPositionVector().getX() > arena->getArenaWidth() / 2) {
			it = bullets->erase(it);
		}
		// checks bottom wall
		if (it->getPositionVector().getY() < -arena->getArenaHeight() / 2) {
			it = bullets->erase(it);
		}
		else {
			it++;
		}
	}
}

void fire_bullet() {
	// Make new bullet on left click press
	Bullet* newBullet = new Bullet();

	// Set in normal variables
	newBullet->setBulletPositionVector(player->getPositionVector().getX(), player->getPositionVector().getY());
	newBullet->setDirectionVector(player->getDirectionVector().getX(), player->getDirectionVector().getY());

	// add Bullet to bullet array
	bullets->push_back(*newBullet);

	// Set counter back to zero
	shipFireRateCounter = 0;

	// check if bullet is outside arena bounds
	checkBulletBounds();
	
	/*
	for (auto bullet = std::begin(*bullets); bullet != std::end(*bullets); ++bullet) {
		printf("Bullets x and y: (%f) (%f) \n", bullet->getPositionVector().getX(), bullet->getPositionVector().getY());
	}
	printf("\n");
	*/

	/*
	float a = bullets->front().getPositionVector().getX();
	float b = bullets->front().getPositionVector().getY();

	float n = bullets->back().getPositionVector().getX();
	float m = bullets->back().getPositionVector().getY();

	float bulletsSize = bullets->size();


	printf("First bullet: (%f) (%f) \n", a, b);
	printf("Last bullet: (%f) (%f) \n", n, m);
	printf("Bullets size: (%f) \n", bulletsSize);
	*/
}



void on_mouse_button(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (shipFireRateCounter >= maxShipFireRate) {
			fire_bullet();
		}
	}
}

void update_game_state(float dt) {
	player->setDt(dt);
	bullet->setDt(dt);

	checkAsteroidSpawn();
}

// function for calculating dt , from lec 2
float calc_dt() {
	float cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	float dt = cur_time - g_last_time;
	g_last_time = cur_time;

	// update counter
	shipFireRateCounter = shipFireRateCounter + dt;
	asteroidSpawnRateCounter = asteroidSpawnRateCounter + dt;

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

	width = w;
	height = h;
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