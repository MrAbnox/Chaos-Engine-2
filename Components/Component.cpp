#include "Component.h"

Component::Component(GameObject* gameObject) :gameObject(gameObject)
{
	this->gameObject = gameObject;
}

Component::Component(const Component& c)
{
	gameObject = c.gameObject;
}


GameObject* Component::getGameObject()
{
	return gameObject;
}

void Component::setGameObject(GameObject& gameObject)
{
	this->gameObject = &gameObject;
}
