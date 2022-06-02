#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include <memory>
#include "../Components/Transform.h"
#include <iostream>

class Component;
class Transform;

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
	void setShouldDestroy(bool& destroy);
	void setName(const std::string& name);
	
	std::string getName() const;
	bool getIsEnabled() const;
	bool getShouldDestroy() const;
	Transform* getTransform();
	const std::vector<std::shared_ptr<Component>>& getComponents();
private:

	std::string name;
	bool isEnabled = true;
	bool shouldDestroy = false;
	bool isStatic;
	bool hastransform = false;
	Transform* transform;
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
