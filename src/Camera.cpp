#include "Camera.h"
#include <iostream>
Camera::Camera(glm::vec3 pos)
{
	positionVector = pos;
	upDir = glm::vec3(0.0f, 1.0f, 0.0f);
	rightDir = glm::vec3(1.0f, 0.0f, 0.0f);
	forwardDir = glm::vec3(0.0f, 0.0f, 1.0f);
	pitchAngle = 0.0f;
	yawAngle = 0.0f;
}

glm::vec3 Camera::getPosition()
{
	return positionVector;
}

glm::mat4 Camera::getViewMatrix()
{
	glm::mat4 Translate = glm::translate(glm::mat4(1.0f),-positionVector);
	glm::mat4 viewR = glm::rotate(glm::mat4(1.0f), glm::radians(yawAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	viewR = glm::rotate(viewR, glm::radians(pitchAngle), rightDir);
	return viewR*Translate;
}

void Camera::moveForward(float dir)
{
	positionVector += forwardDir * 0.1f * dir;
}

void Camera::moveRight(float dir)
{
	positionVector += rightDir * 0.1f * dir;
}

void Camera::moveUp(float dir)
{
	positionVector += upDir * 0.1f * dir;
}

void Camera::rotateYaw(float degrees)
{
	yawAngle = degrees;
	rightDir.x = cosf(glm::radians(yawAngle));
	rightDir.z = sinf(glm::radians(yawAngle));
	forwardDir.x = -sinf(glm::radians(yawAngle));
	forwardDir.z = cosf(glm::radians(yawAngle));
	
}

void Camera::rotatePitch(float degrees)
{
	pitchAngle = degrees;
}

