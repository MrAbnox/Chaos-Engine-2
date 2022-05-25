#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include <memory>
#include "../Components/Transform.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

public:
	void initialize();
	void update();
	void render();

public:

	template <class T>
	std::shared_ptr<T> addComponent();

	template <class T>
	std::shared_ptr<T> getComponent();

	bool removeComponent(std::shared_ptr<Component> component);

public:

	void setIsEnabled(const bool& value);
	bool getIsEnabled() const;

	Transform getTransform() const;

private:

	std::string name;
	bool isEnabled;
	bool shouldDestroy;

	std::vector<std::shared_ptr<Component>> components;

};

template <class T>
inline std::shared_ptr<T> GameObject::addComponent()
{
	auto obj = std::shared_ptr<T>(new T(this));
	components.push_back(obj);

	return obj;
}

// definition of the template member function addComponent
// Usage:
// GameObject* go = something;
// shared_ptr<SpriteComponent> sc = go->addComponent<SpriteComponent>();
template <class T>
inline std::shared_ptr<T> GameObject::getComponent()
{
	for (auto c : components)
	{
		std::shared_ptr<T> res = std::dynamic_pointer_cast<T>(c);
		if (res != nullptr)
		{
			return res;
		}
	}
	return std::shared_ptr<T>();
}

#endif // !GAMEOBJECT_H
