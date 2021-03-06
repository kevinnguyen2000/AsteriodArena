#include "../vs/Arena.h"
#include "../vs/Player.h"
#include "../vs/Types.h"
#include "../vs/Bullet.h"
#include "../vs/Asteroid.h"
#include "../vs/Missile.h"

// Create arena object
Arena* arena = new Arena();

// Create player object
Player* player = new Player();

// Vector for player positon
Vector* playerPosition = new Vector();
// Vector for player direction
Vector* playerDirection = new Vector();

// Vector of bullets
std::vector<Bullet*> bullets;
Bullet* bullet = new Bullet();

float g_last_time = 0.0;

float maxShipFireRate = 0.4;
float shipFireRateCounter = 0;

float maxShipMissileRate = 6;
float shipMissileRateCounter = 0;

// Vector of asteriods
std::vector<Asteroid*> asteroids;
Asteroid* asteroid = new Asteroid();

float maxAsteroidRate = 13;
float asteroidSpawnRateCounter = 0;

float width, height = 0;

float asteroidWave = 1;

// Vector for key states
std::vector<bool> keys;
int keysNum = 4;

// Vector of missiles
std::vector<Missile*> missiles;
Missile* missile = new Missile();

// Math helper
Math* math = new Math();

// Text
std::string scoreText = "Score: ";
int score = 0;
std::string scoreString = "0";
const char* scoreChar = "0";
std::string timeText = "Time: ";
int timeElasped = 0;
std::string timeString = "0";
const char* timeChar = "0";

bool gameOver = false;

void reset_game() {
	// Set collision back to false
	arena->setCollisionFalse();
	// Set player position back to starting state
	player->resetPlayer();
	// clears all bullets on screen
	bullets.clear();
	// clears all asteroids on screen
	asteroids.clear();
	// set asteroid wave back to default
	asteroidWave = 1;
	// clear all missiles
	missiles.clear();
	// set score back to zero
	score = 0;
	scoreString = "0";
	scoreChar = "0";
	// reset time
	gameOver = true;
}

void render_string(float x, float y, void* font, const char* string)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	// Set the projection - use this to render text
	gluOrtho2D(0, arena->getArenaWidth(), 0, arena->getArenaHeight());
	glMatrixMode(GL_MODELVIEW);

	glRasterPos2f(x, y);
	int len = (int)strlen(string);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}

	glMatrixMode(GL_PROJECTION);

	// Restore the original projection matrix for rendering everything else
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
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
	if (asteroids.size() > 0) {
		asteroid->display(asteroids);
	}
	if (missiles.size() > 0) {
		missile->display(missiles);
	}

	glColor3f(1.0, 1.0, 1.0);
	render_string(timeText.length() * 5, arena->getArenaHeight() - timeText.length()*8, GLUT_BITMAP_TIMES_ROMAN_24, "Time: ");
	render_string(timeText.length() * 16, arena->getArenaHeight() - scoreText.length() * 7, GLUT_BITMAP_TIMES_ROMAN_24, timeChar);
	render_string(arena->getArenaWidth() - timeText.length()*20, arena->getArenaHeight() - timeText.length()*8, GLUT_BITMAP_TIMES_ROMAN_24, "Score: ");
	render_string(arena->getArenaWidth() - timeText.length() * 9, arena->getArenaHeight() - timeText.length() * 8, GLUT_BITMAP_TIMES_ROMAN_24, scoreChar);
		
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
		keys[w_key] = true;
		break;
	case 'a':
		keys[a_key] = true;
		break;
	case 'd':
		keys[d_key] = true;
		break;
	case 'z':
		player->switchGunType();
	default:
		break;
	}
}

void on_key_release(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27:
	case 'q':
		exit(EXIT_SUCCESS);
		break;
	case 'w':
		keys[w_key] = false;
		break;
	case 'a':
		keys[a_key] = false;
		break;
	case 'd':
		keys[d_key] = false;
		break;
	default:
		break;
	}
}

void checkAsteroidHasAppeared() {
	for (int i = 0; i < asteroids.size();) {
		if (asteroids[i]->getPositionVector().getX() > -arena->getArenaWidth() / 2 and
			asteroids[i]->getPositionVector().getX() < arena->getArenaWidth() / 2 and 
			asteroids[i]->getPositionVector().getY() < arena->getArenaHeight() / 2 and 
			asteroids[i]->getPositionVector().getY() > -arena->getArenaHeight() / 2 and 
			asteroids[i]->getAppeared() == false) {
			asteroids[i]->setAppearedTrue();
		}
		else {
			i++;
		}
	}
}

void checkClosetAsteroidToMissile() {
	// variable for tracking closet distance
	float nearestDistance = 10000;
	for (int i = 0; i < asteroids.size(); ++i) {
		for (int j = 0; j < missiles.size(); ++j) {
			if (asteroids.size() > 0) {
				// check if asteroid has appeared in arena
				if (asteroids[i]->getAppeared() == true) {
					// check for closet asteroid
					if (missiles[j]->checkDistance(asteroids[i]->getPositionVector().getX(), asteroids[i]->getPositionVector().getY(), missiles[j]->getRadius()) < nearestDistance) {
						nearestDistance = missiles[j]->checkDistance(asteroids[i]->getPositionVector().getX(), asteroids[i]->getPositionVector().getY(), missiles[j]->getRadius());
						// Set missile direction towards the nearest asteroid
						Vector* asteroidPositionVector = new Vector();
						asteroidPositionVector->setX(asteroids[i]->getPositionVector().getX());
						asteroidPositionVector->setY(asteroids[i]->getPositionVector().getY());
						missiles[j]->missileDirectionToAsteroid(asteroidPositionVector);
						break;
					}
				}
			}
		}
	}
}

void checkBulletBounds() {
	for (int i = 0; i < bullets.size();) {
		if (bullets[i]->getPositionVector().getX() < -arena->getArenaWidth() / 2) {
			delete bullets[i];
			bullets[i] = nullptr;
			bullets.erase(bullets.begin() + i);
		}
		// checks top wall
		if (bullets[i]->getPositionVector().getY() > arena->getArenaHeight() / 2) {
			delete bullets[i];
			bullets[i] = nullptr;
			bullets.erase(bullets.begin() + i);
		}
		// checks right wall
		if (bullets[i]->getPositionVector().getX() > arena->getArenaWidth() / 2) {
			delete bullets[i];
			bullets[i] = nullptr;
			bullets.erase(bullets.begin() + i);
		}
		// checks bottom wall
		if (bullets[i]->getPositionVector().getY() < -arena->getArenaHeight() / 2) {
			delete bullets[i];
			bullets[i] = nullptr;
			bullets.erase(bullets.begin() + i);
		}
		else {
			i++;
		}
	}
}

void fire_missile() {
	Missile* newMissile = new Missile();

	// shoots from tip of ship
	player->multiplyDirectionVector();

	newMissile->setMissilePositionVector(player->getPositionVector().getX() + player->getMultipliedDirectionVector().getX(), player->getPositionVector().getY() + player->getMultipliedDirectionVector().getY());

	// add new missile to vector
	missiles.push_back(newMissile);

	shipMissileRateCounter = 0;
}

void fire_bullet() {
	// Make new bullet on left click press
	Bullet* newBullet = new Bullet();

	// shoots from tip of ship
	player->multiplyDirectionVector();

	// Set in normal variables, add positon and direction vector to make bullet spawn at tip
	newBullet->setBulletPositionVector(player->getPositionVector().getX() + player->getMultipliedDirectionVector().getX(), player->getPositionVector().getY() + player->getMultipliedDirectionVector().getY());
	newBullet->setDirectionVector(player->getDirectionVector().getX(), player->getDirectionVector().getY());

	// add Bullet to bullet array
	bullets.push_back(newBullet);

	// Set counter back to zero
	shipFireRateCounter = 0;

	// check if bullet is outside arena bounds
	checkBulletBounds();
}

void checkAsteroidSpawn() {
	if (asteroidSpawnRateCounter >= maxAsteroidRate) {
		// Clear previous asteroids before new wave
		asteroids.clear();

		// Loop through asteroid waves
		for (int i = 0; i < asteroidWave; i++) {
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
			asteroids.push_back(newAsteroid);
		}

		// add one to wave counter
		asteroidWave++;

		// Set asteroid counter back to zero
		asteroidSpawnRateCounter = 0;
	}
}

void checkBulletAsteroidCollision() {
	for (int i = 0; i < asteroids.size();) {
		bool asteroidDestroyed = false;
		for (int j = 0; j < bullets.size();) {
			if (asteroids[i]->checkCollision(bullets[j]->getPositionVector().getX(), bullets[j]->getPositionVector().getY(), 1) == true) {
				delete bullets[j];
				bullets[j] = nullptr;
				bullets.erase(bullets.begin() + j);
				asteroids[i]->decreaseHP(1);
				if (asteroids[i]->getHP() <= 0) {
					delete asteroids[i];
					asteroids[i] = nullptr;
					asteroids.erase(asteroids.begin() + i);
					asteroidDestroyed = true;
					// add score by one
					score = score + 1;
					scoreString = std::to_string(score);
					scoreChar = scoreString.c_str();
				}
				break;
			}
			else {
			j++;
			}
		}
		if (!asteroidDestroyed) {
			i++;
		}
	}
}

void checkMissileAsteroidCollision() {
	for (int i = 0; i < asteroids.size();) {
		bool asteroidDestroyed = false;
		for (int j = 0; j < missiles.size();) {
			if (asteroids[i]->checkCollision(missiles[j]->getPositionVector().getX(), missiles[j]->getPositionVector().getY(), missiles[j]->getRadius()) == true) {
				delete missiles[j];
				missiles[j] = nullptr;
				missiles.erase(missiles.begin() + j);
				asteroids[i]->decreaseHP(3);
				if (asteroids[i]->getHP() <= 0) {
					delete asteroids[i];
					asteroids[i] = nullptr;
					asteroids.erase(asteroids.begin() + i);
					asteroidDestroyed = true;
					// add score by one
					score = score + 1;
					scoreString = std::to_string(score);
					scoreChar = scoreString.c_str();
				}
				break;
			}
			else {
				j++;
			}
		}
		if (!asteroidDestroyed) {
			i++;
		}
	}
}

void checkPlayerAsteroidCollision() {
	// lopp through all asteroids
	for (int i = 0; i < asteroids.size(); i++) {
		if (asteroids[i]->checkCollision(player->getPositionVector().getX(), player->getPositionVector().getY(), player->getPlayerRadius()) == true) {
			reset_game();
		}
	}
}

void on_mouse_button(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		keys[m1] = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		keys[m1] = false;
	}
}

void checkKeyStates() {
	if (keys[m1] == true) {
		if (player->getGunType() == "normal") {
			if (shipFireRateCounter >= maxShipFireRate) {
				fire_bullet();
			}
		}
		if (player->getGunType() == "missile") {
			if (shipMissileRateCounter >= maxShipMissileRate) {
				fire_missile();
			}
		}
	}
	if (keys[w_key] == true) {
		player->moveFoward();
		// Check wall collision
		*playerPosition = player->getPositionVector();
		arena->setCircleWorldPositionVector(playerPosition);
		arena->checkWallCollision();
		if (arena->getCollision() == true) {
			reset_game();
		}
	}
	if (keys[w_key] == false) {
		player->slowDown();
		// Check wall collision
		*playerPosition = player->getPositionVector();
		arena->setCircleWorldPositionVector(playerPosition);
		arena->checkWallCollision();
		if (arena->getCollision() == true) {
			reset_game();
		}
	}
	if (keys[a_key] == true) {
		player->rotateLeft();
	}
	if (keys[d_key] == true) {
		player->rotateRight();
	}
}

void update_game_state(float dt) {

	checkKeyStates();

	player->setDt(dt);
	bullet->setDt(dt);
	asteroid->setDt(dt);
	missile->setDt(dt);

	checkAsteroidSpawn();
	checkClosetAsteroidToMissile();

	// check if an asteroid needs to be erased
	checkAsteroidHasAppeared();

	// check bullet collision with asteroids
	if (bullets.size() > 0 and asteroids.size() > 0) {
		checkBulletAsteroidCollision();
	}
	// check asteroid collision with player
	if (asteroids.size() > 0) {
		checkPlayerAsteroidCollision();
	}
	// check missile collision with asteroid
	if (missiles.size() > 0 and asteroids.size() > 0) {
		checkMissileAsteroidCollision();
	}
}

// function for calculating dt , from lec 2
float calc_dt() {
	float cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0 - timeElasped;
	float dt_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	float dt = dt_time - g_last_time;
	g_last_time = dt_time;

	// update counter
	shipFireRateCounter = shipFireRateCounter + dt;
	asteroidSpawnRateCounter = asteroidSpawnRateCounter + dt;
	shipMissileRateCounter = shipMissileRateCounter + dt;

	// update game timer
	timeString = std::to_string(int(cur_time));
	timeChar = timeString.c_str();

	if (gameOver == true) {
		timeElasped = timeElasped + cur_time;
		gameOver = false;
	}

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
	glutKeyboardUpFunc(on_key_release);
	glutMouseFunc(on_mouse_button);
	
	// init vector keys
	for (int i = 0; i < keysNum; i++) {
		keys.push_back(false);
	}

	// idle function
	glutIdleFunc(on_idle);
}

int main(int argc, char** argv)
{
	init(&argc, argv);
	run_app();
	return EXIT_SUCCESS;
}