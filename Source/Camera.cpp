#include "Camera.h"

Camera::Camera(glm::vec3 cam_pos, glm::vec3 look_pos, glm::vec3 up_dir)
{
	this->camPos = cam_pos;
	this->lookPos = look_pos;
	this->upDir = up_dir;
	updateViewMat();
}

Camera::~Camera() {}

void Camera::move(Camera::Direction direct)
{
	// Get Movement
	glm::vec3 movement = glm::vec3(0.0, 0.0, 0.0);
	switch (direct)
	{
	case Camera::UP:
		movement = this->upDir * this->moveSpeedFactor;
		break;
	case Camera::DOWN:
		movement = -this->upDir * this->moveSpeedFactor;
		break;
	case Camera::LEFT:
		movement = this->getLeftDir() * this->moveSpeedFactor;
		break;
	case Camera::RIGHT:
		movement = this->getRightDir() * this->moveSpeedFactor;
		break;
	default:
		break;
	}

	// update members
	camPos += movement;
	lookPos += movement;
	this->updateViewMat();
}

void Camera::rotateWithMouse(int move_x, int move_y)
{
	// get rotate matrix
	glm::vec3 mouseMoveInSpace = (float)move_x * this->getRightDir() + (float)move_y * this->getUpDir();
	glm::vec3 rotateAxis = glm::cross(mouseMoveInSpace, this->getLookDir());
	glm::mat4 rotateMat = glm::rotate(glm::mat4(), glm::length(mouseMoveInSpace) * rotateSpeedFactor, rotateAxis);
	
	// rotate lookDir and upDir
	// lookDir
	glm::vec4 look_dir = rotateMat * glm::vec4(this->getLookDir(), 0.0);
	this->lookPos = this->camPos + glm::vec3(look_dir);

	// upDir
	glm::vec4 up_dir = rotateMat * glm::vec4(this->getLookDir(), 0.0);
	this->upDir = glm::vec3(up_dir);

	this->updateViewMat();
}

void Camera::updateViewMat()
{
	this->viewMatrix = glm::lookAt(this->camPos, this->lookPos, this->upDir);
}

glm::vec3 Camera::getCamPos()
{
	return  this->camPos;
}

glm::vec3 Camera::getLookDir()
{
	return glm::normalize(this->lookPos - this->camPos);
}

glm::vec3 Camera::getUpDir()
{
	return glm::normalize(this->upDir);
}

glm::vec3 Camera::getLeftDir()
{
	glm::vec3 left = glm::cross(this->getUpDir(), this->getLookDir());
	return glm::normalize(left);
;}

glm::vec3 Camera::getRightDir()
{
	return -this->getLeftDir();
}