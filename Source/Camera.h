#ifndef GPA_ASS2_CAMERA_H
#define GPA_ASS2_CAMERA_H

#include "GLIncludes.h"

class Camera 
{
public:
	enum Direction { UP, DOWN, LEFT, RIGHT, FRONT, BACK};

	Camera(glm::vec3 CamPos, glm::vec3 LookPos, glm::vec3 UpDir);
	~Camera();
	void moveLocal(Direction direct);
	void rotateWithMouse(int mouse_x, int mouse_y);
	glm::vec3 getLookDir();
	glm::vec3 getUpDir();
	glm::vec3 getLeftDir();
	glm::vec3 getRightDir();
	glm::vec3 getCamPos();
	glm::mat4 getViewMat();

private:
	glm::mat4 viewMatrix;
	glm::vec3 camPos;
	glm::vec3 lookPos;
	glm::vec3 upDir;
	float rotateSpeedFactor = 0.0001f;
	float moveSpeedFactor = 0.05f;
	struct {
		int x = -1, y = -1;
	} lastMouse;

	void updateViewMat();
};

#endif