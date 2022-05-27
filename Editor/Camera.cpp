#include "Camera.h"
#include "../Application/Window.h"
#include <iostream>

Camera::Camera(GameObject* object) : Component(gameObject)
{
	this->gameObject = gameObject;

	setDefault(glm::vec3(0.0f, 0.0f, -3.0f));
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
	glm::vec2 screenSize = Window::instance()->getScreenSize();
	proj = glm::perspective(glm::radians(zoom), (float)screenSize.x / (float)screenSize.y, 0.1f, 100.0f);
	viewProj = proj * view;
	shader.Use();
	shader.setUniform("view", view);
	shader.setUniform("projection", proj);

	std::cout << "Send Camera data" << std::endl;
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
