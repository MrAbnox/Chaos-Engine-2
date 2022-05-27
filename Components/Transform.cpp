#include "Transform.h"

Transform::Transform(GameObject* object) : Component(gameObject)
{
	this->gameObject = gameObject;
}

void Transform::sendData(Shader& shader)
{
	shader.setUniform("model", model);
}
