#include "../Include/Common.h"

using namespace glm;

void MyDisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

int main(int argc, char *argv[]) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("ASS2_106062222");

	glutDisplayFunc(MyDisplayFunc);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutMainLoop();
	return 0;
}