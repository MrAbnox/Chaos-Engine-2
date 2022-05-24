#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	// remove reference to this in components
	for (auto& c : components)
	{
		c->gameObject = nullptr;
	}
	//TODO:: Figure out what to do with transform
	//delete(transform);
	//transform = nullptr;
}
