#include <GL/freeglut.h>
#include <iostream>
void drawCircle(float x, float y, float r, int amountSegments);
void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	//glClearColor(0, 0, 0, 1.0);
	drawCircle(400, 200, 100, 20);
	glFlush();
}

void Initialize(int w, int h) {
	glClearColor(0.8, 1.0, 0.6, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-200.0, 200.0, -200.0, 200.0, -5.0, 5.0);
	//glOrtho2D(0, w, 0, h);
	gluOrtho2D(0, w, 0, h);
}
void drawCircle(float x, float y, float r, int amountSegments)
{
	glBegin(GL_LINE_LOOP);
	glClearColor(0, 0, 0, 1.0);
	for (int i = 0; i < amountSegments; i++)
	{
		float angle = 2.0 * 3.1415926 * float(i) / float(amountSegments);

		float dx = r * cosf(angle);
		float dy = r * sinf(angle);

		glVertex2f(x + dx, y + dy);
	}
	glEnd();
}

int main(int argc, char ** argv) {
	int width = 800, height = 400;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Our first GLUT application!");
	glutDisplayFunc(Display);
	Initialize(width, height);
	//
	
	glutMainLoop();
	//glClearColor(0, 0, 0, 1.0);
	
	return 0;
}