#include "GameObject.h"
#include "../Components/MeshRenderer.h"

GameObject::GameObject()
{
	addComponent<Transform>();
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

void GameObject::initialize()
{
}

void GameObject::update()
{
	if(isEnabled)
	{
		for (auto& c : components)
		{
			c->update();
		}
	}
}

void GameObject::render()
{
	if (isEnabled)
	{
		for (auto& c : components)
		{
			auto mr = std::dynamic_pointer_cast<MeshRenderer>(c);

			//TODO: Make sure this works
			if (mr != nullptr)
				mr.get()->render();
		}
	}
}

bool GameObject::removeComponent(std::shared_ptr<Component> component)
{
	auto comp = std::find(components.begin(), components.end(), component);
	if (comp != components.end())
	{
		components.erase(comp);
	}

	return true;
}

void GameObject::setIsEnabled(const bool& value)
{
	isEnabled = value;
}

void GameObject::setShouldDestroy(bool& destroy)
{
	shouldDestroy = destroy;
}

bool GameObject::getIsEnabled() const
{
	return isEnabled;
}

bool GameObject::getShouldDestroy() const
{
	return shouldDestroy;
}

Transform* GameObject::getTransform()
{
	return transform;
}