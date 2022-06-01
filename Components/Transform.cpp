#include "Transform.h"
#include <iostream>
#include "../Application/Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform(GameObject* object) : Component(gameObject)
{
	this->gameObject = gameObject;
	model = glm::mat4(1.0f);
	//model = glm::scale(model, glm::vec3(10.0f));
}

void Transform::sendData(Shader& shader)
{
	shader.Use();
	shader.setUniform("model", model);

	Renderer::instance()->getShader("Default").Use();
	Renderer::instance()->getShader("Default").setUniform("model", model);
}

glm::mat4* Transform::getModel()
{
	return &model;
}
