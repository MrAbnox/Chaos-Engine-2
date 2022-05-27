#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include <memory>
#include "../Components/Transform.h"

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
	
	bool getIsEnabled() const;
	bool getShouldDestroy() const;
	Transform* getTransform();

private:

	std::string name;
	bool isEnabled;
	bool shouldDestroy;
	bool isStatic;
	bool hastransform = false;
	Transform* transform;
	std::vector<std::shared_ptr<Component>> components;
	
};

template <class T>
inline std::shared_ptr<T> GameObject::addComponent()
{
	auto obj = std::shared_ptr<T>(new T(this));

	auto temp = std::dynamic_pointer_cast<Transform>(obj);

	//TODO: Make sure this works
	if (temp)
	{
		//TRANSFORM FOUND
		/*if (transform == nullptr)
			transform = obj;
		else
			return nullptr;*/
	}

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
