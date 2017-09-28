#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h> 

float rot = 0;
float dx = 0;
bool checkFlag = true;

static void resize(int width, int height)
{
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(1, 0, 0);

	glPushMatrix();
	glTranslated(dx, 1.5, -6);
	glutWireSphere(1, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, -1.2, -6);
	glRotated(rot, 0.0, 1.0, 0.0);
	glutWireTorus(0.4, 0.8, 10, 20);
	glPopMatrix();

	rot += 3.0;
	if (rot >= 360)
		rot -= 360;

	if (checkFlag)
	{
		dx += 0.1;
		if (dx >= 1.5)
		{
			checkFlag = false;
		}
	}
	else
	{
		dx -= 0.1;
		if (dx <= -1.5)
		{
			checkFlag = true;
		}
	}

	glutSwapBuffers();
}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(50, Timer, 0);
}


/* Program entry point */

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Lab_1_1");

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutTimerFunc(50, Timer, 0);

	glClearColor(1, 1, 1, 1);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glutMainLoop();

	return EXIT_SUCCESS;
}