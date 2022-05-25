#include "Component.h"

Component::Component(GameObject* gameObject) :gameObject(gameObject)
{
}

GameObject* Component::getGameObject()
{
	return gameObject;
}

void Component::setGameObject(GameObject* gameObject)
{
	this->gameObject = gameObject;
}
