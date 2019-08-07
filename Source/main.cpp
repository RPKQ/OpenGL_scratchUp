#include "Program.h"
#include "Loader.h"
#include "Model.h"
#include "Camera.h"
#include "../Source/GLIncludes.h"

using namespace glm;
using namespace std;

const int windowW = 1024, windowH = 768;

glm::mat4 modelMat;
glm::mat4 perspectMat;

Program* program;
Model* model;
Camera* cam;

GLubyte timer_cnt = 0;
bool timer_enabled = true;
unsigned int timer_speed = 16;

void DisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	//modelMat = glm::rotate(glm::mat4(), (float)glutGet(GLUT_ELAPSED_TIME) / 500.0f, glm::vec3(1.0, 0.0, 0.0));
	//modelMat = modelMat * glm::rotate(glm::mat4(), (float)glutGet(GLUT_ELAPSED_TIME) / 500.0f, glm::vec3(0.0, 1.0, 0.0));
	modelMat = glm::mat4(1.0);
	program->setMat4("perspectMat", perspectMat);
	program->setMat4("modelMat", modelMat);
	program->setMat4("viewMat", cam->getViewMat());

	model->draw(program);

	glutSwapBuffers();
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		cam->moveLocal(Camera::FRONT);
		break;
	case 's':
		cam->moveLocal(Camera::BACK);
		break;
	case 'a':
		cam->moveLocal(Camera::LEFT);
		break;
	case 'd':
		cam->moveLocal(Camera::RIGHT);
		break;
	case 'z':
		cam->moveLocal(Camera::UP);
		break;
	case 'x':
		cam->moveLocal(Camera::DOWN);
		break;
	default:
		break;
	}
}

void MotionFunc(int moveX, int moveY)
{
	cam->rotateWithMouse(moveX, moveY);
}

void MouseFunc(int button, int state, int x, int y) {
	if (state == GLUT_UP) 
	{
		cam->endOfRotate();
	}
}

void TimerFunc(int val)
{
	timer_cnt++;
	glutPostRedisplay();
	if (timer_enabled)
	{
		glutTimerFunc(timer_speed, TimerFunc, val);
	}
}

void ReshapeFunc(int width, int height)
{
	glViewport(0, 0, width, height);
	float viewportAspect = (float)width / (float)height;
	perspectMat = glm::perspective(glm::radians(60.0f), viewportAspect, 0.1f, 1000.0f);
}

void InitCallbackFuncs() 
{
	glutDisplayFunc(DisplayFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutMotionFunc(MotionFunc);
	glutMouseFunc(MouseFunc);
	glutTimerFunc(timer_speed, TimerFunc, 0);
	glutReshapeFunc(ReshapeFunc);
}

void Init()
{
	// setup camera
	cam = new Camera(vec3(0.0f, 15.0f, 20.0f), vec3(0.0f, 15.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	// setup program
	const char* fsFilePath = "fs.fs.glsl";
	const char* vsFilePath = "vs.vs.glsl";
	program = new Program(vsFilePath, fsFilePath);
	
	// load models
	model = Loader::loadModel("torso.obj");

	// callbacks
	InitCallbackFuncs();

	ReshapeFunc(windowW, windowH);
}


int main(int argc, char *argv[]) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Window");

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	glClearColor(1.0, 1.0, 1.0, 0.0);

	Init();

	glutMainLoop();

	return 0;
}