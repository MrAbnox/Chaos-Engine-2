#include "Camera.h"
#include "../Application/Window.h"
#include <iostream>


Camera::Camera(GameObject* object) : Component(gameObject)
{
	this->gameObject = gameObject;

	setDefault(glm::vec3(-5.0f, 1.0f, -10.0f));
	Window::instance()->setCamera(this);
}

void Camera::update()
{
	GLFWwindow* window = Window::instance()->getWindow();
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		ProcessKeyboard(FORWARD);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		ProcessKeyboard(BACKWARD);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		ProcessKeyboard(LEFT);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		ProcessKeyboard(RIGHT);
}

void Camera::render()
{
	//sendData();
}

void Camera::setDefault(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
	this->position = position;
	this->up = up;
	worldUp = up;
	this->yaw = yaw;	
	this->pitch = pitch;
	zoom = ZOOM;
}

void Camera::sendData(Shader& shader)
{
	view = getViewMatrix();
	//view = glm::lookAt(position, glm::vec3(0.0f), up);/* Renderer::instance()->getCube()->getTransform()->getModel());*/
	glm::vec2 screenSize = Window::instance()->getScreenSize();
	proj = glm::perspective(glm::radians(zoom), (float)screenSize.x / (float)screenSize.y, 0.1f, 100.0f);
	viewProj = proj * view;
	shader.Use();
	shader.setUniform("view", view);
	shader.setUniform("projection", proj);
	//std::cout << "Send Camera data" << std::endl;
}

void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::ProcessKeyboard(Camera_Movement direction)
{
	float velocity = SPEED;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= SENSITIVITY;
	yoffset *= SENSITIVITY;

	yaw += xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}
