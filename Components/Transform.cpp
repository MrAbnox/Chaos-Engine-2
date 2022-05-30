#include "Transform.h"
#include <iostream>

Transform::Transform(GameObject* object) : Component(gameObject)
{
	this->gameObject = gameObject;
}

void Transform::sendData(Shader& shader)
{
	shader.Use();
	shader.setUniform("model", model);
}
