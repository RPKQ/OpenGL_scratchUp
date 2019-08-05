#include "Program.h"
#include "../Source/GLIncludes.h"

using namespace glm;
using namespace std;

GLuint VBO;
Program* program;
vec3 tianglePos[3] = {
	vec3(0.0, 0.0, 0.0), vec3(-0.5, 0, 0), vec3(0.5, 0.5, 0.0) 
};

void MyDisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(tianglePos), &tianglePos, GL_STATIC_DRAW);
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

	printf("here\n");

	const char* fsFilePath = "fs.fs.glsl";
	const char* vsFilePath = "vs.vs.glsl";
	program = new Program(vsFilePath, fsFilePath);

	CreateVBO();

	glutMainLoop();
	return 0;
}