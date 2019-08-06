#include "Program.h"
#include "Model.h"
#include "../Source/GLIncludes.h"

using namespace glm;
using namespace std;

GLuint VBO;
Program* program;
Model* model;
vec3 tianglePos[3] = {
	vec3(0.0, 0.0, 0.0), vec3(-0.5, 0, 0), vec3(0.5, 0.5, 0.0) 
};

void MyDisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT);
	program->use();

	model->draw(program);

	glutSwapBuffers();
}

void InitCallbackFuncs() 
{
	glutDisplayFunc(MyDisplayFunc);
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

	const char* fsFilePath = "fs.fs.glsl";
	const char* vsFilePath = "vs.vs.glsl";
	program = new Program(vsFilePath, fsFilePath);
	
	model = new Model("ladybug.obj");

	glutMainLoop();
	return 0;
}