#include "Transform.h"
#include <iostream>
#include "../Application/Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform(GameObject* object) : Component(gameObject)
{
	this->gameObject = gameObject;
	model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(0.2f));
	sl = glm::vec3(0.2f);
}

void Transform::sendData(Shader& shader)
{
	shader.Use();
	shader.setUniform("model", model);

	//Renderer::instance()->getShader("Default").Use();
	//Renderer::instance()->getShader("Default").setUniform("model", model);
}

glm::mat4* Transform::getModel()
{
	return &model;
}

void Transform::setPos(glm::vec3 pos)
{
	position = pos;
	model = glm::translate(glm::mat4(1), position);
	model = glm::scale(model, sl);
}

void Transform::setScale(glm::vec3 scale)
{
	model = glm::scale(model, scale);
	this->sl = scale;
}

void Transform::translate(glm::vec3 pos)
{
	this->position += pos;
	model = glm::translate(glm::mat4(1), position);
}
