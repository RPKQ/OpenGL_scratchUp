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

void MyDisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	modelMat = glm::rotate(glm::mat4(), (float)glutGet(GLUT_ELAPSED_TIME) / 500.0f, glm::vec3(1.0, 0.0, 0.0));
	modelMat = modelMat * glm::rotate(glm::mat4(), (float)glutGet(GLUT_ELAPSED_TIME) / 500.0f, glm::vec3(0.0, 1.0, 0.0));

	program->setMat4("perspectMat", perspectMat);
	program->setMat4("modelMat", modelMat);
	program->setMat4("viewMat", cam->getViewMat());

	model->draw(program);

	glutSwapBuffers();
}

void MyKeyboardFunc(unsigned char key, int x, int y)
{
	printf("%c pressed\n", key);
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

void MyMotionFunc(int moveX, int moveY)
{
	/*printf("camPos: ");
	printVec3(cam->getCamPos());
	printf("lookDir: ");
	printVec3(cam->getLookDir());
	printf("upDir: ");
	printVec3(cam->getUpDir());*/

	cam->rotateWithMouse(moveX, moveY);
}

void MyTimerFunc(int val)
{
	timer_cnt++;
	glutPostRedisplay();
	if (timer_enabled)
	{
		glutTimerFunc(timer_speed, MyTimerFunc, val);
	}
}

void MyReshapeFunc(int width, int height)
{
	glViewport(0, 0, width, height);
	float viewportAspect = (float)width / (float)height;
	perspectMat = glm::perspective(glm::radians(60.0f), viewportAspect, 0.1f, 1000.0f);
}

void InitCallbackFuncs() 
{
	glutDisplayFunc(MyDisplayFunc);
	glutKeyboardFunc(MyKeyboardFunc);
	glutMotionFunc(MyMotionFunc);
	glutTimerFunc(timer_speed, MyTimerFunc, 0);
	glutReshapeFunc(MyReshapeFunc);
}

void Init()
{
	// setup camera
	cam = new Camera(vec3(-10.0f, 5.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	// setup program
	const char* fsFilePath = "fs.fs.glsl";
	const char* vsFilePath = "vs.vs.glsl";
	program = new Program(vsFilePath, fsFilePath);
	
	// load models
	model = Loader::loadModel("Cube.obj");

	// callbacks
	InitCallbackFuncs();

	MyReshapeFunc(windowW, windowH);
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