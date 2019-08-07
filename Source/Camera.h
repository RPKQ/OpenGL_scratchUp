#ifndef GPA_ASS2_CAMERA_H
#define GPA_ASS2_CAMERA_H

#include "GLIncludes.h"

class Camera 
{
public:
	enum Direction { UP, DOWN, LEFT, RIGHT };

	Camera(glm::vec3 CamPos, glm::vec3 LookPos, glm::vec3 UpDir);
	~Camera();
	void move(Direction direct);
	void rotateWithMouse(int Mousex, int Mousey);
	glm::vec3 getLookDir();
	glm::vec3 getUpDir();
	glm::vec3 getLeftDir();
	glm::vec3 getRightDir();
	glm::vec3 getCamPos();

private:
	glm::mat4 viewMatrix;
	glm::vec3 camPos;
	glm::vec3 lookPos;
	glm::vec3 upDir;
	float rotateSpeedFactor = 1.0;
	float moveSpeedFactor = 1.0;

	void updateViewMat();
};

#endif