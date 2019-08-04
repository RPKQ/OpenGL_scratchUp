#include "../Include/Common.h"

using namespace glm;

GLuint VBO;
vec3 vertexPos = vec3(0.0, 0.0, 0.0);

void MyDisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_POINTS, 0, 1);

	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

void InitCallbackFuncs() 
{
	glutDisplayFunc(MyDisplayFunc);
}

void CreateVBO() 
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPos), &vertexPos, GL_STATIC_DRAW);
}

int main(int argc, char *argv[]) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Window");

	InitCallbackFuncs();

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	glClearColor(0.0, 0.0, 0.0, 0.0);

	CreateVBO();

	glutMainLoop();
	return 0;
}