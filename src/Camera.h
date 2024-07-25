#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Camera
{
private:
	//angles
	float yawAngle;
	float pitchAngle;
	//direction Vectors
	glm::vec3 rightDir;
	glm::vec3 upDir;
	glm::vec3 forwardDir;
	glm::vec3 lookVec;
	GLFWwindow* window;
	glm::vec3 positionVector;
public:
	Camera(GLFWwindow* window, glm::vec3 pos = glm::vec3(0, 0, 0));
	glm::vec3 getPosition();
	glm::mat4 getViewMatrix();
	void moveForward(float dir);
	void moveRight(float dir);
	void moveUp(float  dir);
	void rotateYaw(float degrees);
	void rotatePitch(float degrees);
	inline glm::vec2 getXZposition() { return glm::vec2(positionVector.x, positionVector.z); }
	inline glm::vec3 getForwardVec() { return forwardDir; }
	inline glm::vec3 getLookVec() { return lookVec;}
	int width();
	int height();
};