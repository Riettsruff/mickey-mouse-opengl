#include <iostream>
#include <GL/freeglut.h>

const int FPS = 100;

float x1PosBox = 50.0f;
float x2PosBox = 25.0f;

float xBoxVelocity = 21.0f;

float xPosLeftEye = 202.0f;
float xPosRightEye = 282.0f;

float xLeftEyeVelocity = 0.75f;
float xRightEyeVelocity = 0.75f;

void cone(float TITIK_LAYAR_X, float TITIK_LAYAR_Y,
	float LEBAR_X, float LEBAR_Y, float JUMLAH_SUDUT, float ROTASI) {
	GLfloat derajat = (360.0f / JUMLAH_SUDUT) * 3.14 / 100.0f;
	glBegin(GL_TRIANGLE_FAN);
	GLfloat sudut = 0.0f - ROTASI;
	for (int _k = 0; _k < JUMLAH_SUDUT; ++_k) {
		glVertex2f(
			TITIK_LAYAR_X + (LEBAR_X * cos(sudut)),
			TITIK_LAYAR_Y + (LEBAR_Y * sin(sudut))
		);
		sudut += derajat;
	}
	glEnd();
}

void circle(float x, float y, float radius, bool isFill) {
	int triangleAmount = 100;
	float triplePI = 3.0f * 3.14f;
	
	for (int j = 0; j < 2; ++j) {
		glBegin(isFill ? GL_TRIANGLE_FAN : GL_LINE_LOOP);
		glVertex2f(x, y);
		for (int i = 0; i <= triangleAmount; ++i) {
			glVertex2f(
				x + (radius * cos(i * triplePI / triangleAmount)),
				y + (radius * sin(i * triplePI / triangleAmount))
			);
		}
		glEnd();
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(0, 0, 0);
	circle(100.0, 425.0, 60.0, true);
	circle(400.0, 425.0, 60.0, true);
	circle(250.0, 290.0, 150.0, true);
	
	for (int i = 0; i < 50; ++i) {
		glColor3ub(216, 144, 52);
		cone(215, 220, 75, 100 + i, 1000, 50);
		cone(285, 220, 75, 100 + i, 1000, 50);
		cone(250, 200, 70 + i - 1, 100 + i - 10, 1000, 50);
		cone(250, 190, 150 + i, 70, 1000, 50);
	
		glColor3ub(255, 255, 255);
		cone(290, 260, 30, 10 + i, 1000, 50);
		cone(210, 260, 30, 10 + i, 1000, 50);

		glColor3ub(0, 0, 0);
		cone(xPosRightEye, 230, 15, -15 + i, 1000, 50);
		cone(xPosLeftEye, 230, 15, -15 + i, 1000, 50);
	}

	glBegin(GL_QUADS);
		glColor3ub(216, 144, 52);
		glVertex2f(390, 220);
		glVertex2f(180, 220);
		glVertex2f(180, 190);
		glVertex2f(390, 190);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glColor3ub(149, 81, 25);
		glVertex2f(350, 220);
		glVertex2f(150, 220);
	glEnd();

	for (int i = 0; i < 50; ++i) {
		glColor3ub(149, 81, 25);
		circle(250.0, 160.0, 57.0, false);
	}

	glBegin(GL_POLYGON);
		glColor3ub(216, 144, 52);
		glVertex2f(150, 215);
		glVertex2f(350, 215);
		glVertex2f(350, 145);
		glVertex2f(150, 145);
	glEnd();

	for (int i = 0; i < 50; ++i) {
		glColor3ub(0, 0, 0);
		cone(250, 178, -5 + i, -20 + i, 1000, 50);
	}

	glBegin(GL_QUADS);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2f(x1PosBox, 50.0f);
		glVertex2f(x1PosBox, 25.0f);
		glVertex2f(x2PosBox, 25.0f);
		glVertex2f(x2PosBox, 50.0f);
	glEnd();

	glutSwapBuffers();
}

void animate(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, animate, 0);

	xPosLeftEye += xLeftEyeVelocity;
	xPosRightEye += xRightEyeVelocity;

	if (xPosLeftEye < 202.0f || xPosLeftEye > 219.0f) xLeftEyeVelocity = -xLeftEyeVelocity;
	if (xPosRightEye < 282.0f || xPosRightEye > 299.0f) xRightEyeVelocity = -xRightEyeVelocity;

	x1PosBox += xBoxVelocity;
	x2PosBox += xBoxVelocity;

	if (x2PosBox < 0.0f || x1PosBox > 499.0f) xBoxVelocity = -xBoxVelocity;
}

void initGL() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TTS OpenGL");
	glutDisplayFunc(display);

	initGL();

	glutTimerFunc(0, animate, 0);

	glutMainLoop();

	return 0;
}