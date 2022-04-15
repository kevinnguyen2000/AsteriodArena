#include "Missile.h";

Missile::Missile() {
	this->positionVector = new Vector();
	this->directionVector = new Vector();
	this->math = new Math();
	this->angle = 0;
	this->dt = 0;
	this->movementSpeed = 0;
}

void Missile::setDt(float dt) {
	this->dt = dt;
}

void Missile::display(std::vector<Missile*> missiles) {
	for (Missile* missile : missiles) {
		glPushMatrix();
		glLoadIdentity();

		//printf("First bullet: (%f) (%f) \n", bullet.positionVector->getX(), bullet.positionVector->getY());

		glColor3f(1.0, 1.0, 1.0);
		glPointSize(5.0);
		glTranslatef(missile->positionVector->getX(), missile->positionVector->getY(), 0.0f);
		glRotatef(missile->angle, 0.0f, 0.0f, 1.0f);
		glScalef(0.0f, 0.0f, 0.0f);

		glBegin(GL_POINTS);
		glVertex3f(0.0, 0.0, 0.0);
		glEnd();
		glPopMatrix();

		// Method to track closet asteroid
		// bulletDirection(*bullet);

	}
}

void Missile::setMissilePositionVector(float x, float y) {
	this->positionVector->setX(x);
	this->positionVector->setY(y);
}

void Missile::setDirectionVector(float x, float y) {
	this->directionVector->setX(x);
	this->directionVector->setY(y);
}