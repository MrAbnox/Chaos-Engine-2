#include "GameObject.h"
#include "../Components/MeshRenderer.h"
#include "../Editor/Camera.h"
#include "../Application/Renderer.h"

GameObject::GameObject()
{
	transform = new Transform(this);
	//components.push_back(std::make_shared<Transform>(*transform));
	//components.size();
	//transform = temp.get();
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
			{
				mr.get()->render();
				continue;
			}

			auto cam = std::dynamic_pointer_cast<Camera>(c);

			//TODO: Make sure this works
			if (cam != nullptr)
			{
				/*auto temp = getComponent<MeshRenderer>()->getMaterial().getShader();*/
				//cam.get()->sendData(Renderer::instance()->getShader("Default"));
				cam.get()->sendData(Renderer::instance()->getShader("Skybox"));
				cam.get()->sendData(Renderer::instance()->getShader("Default"));
			}
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

const std::vector<std::shared_ptr<Component>>& GameObject::getComponents()
{
	return components;
}
