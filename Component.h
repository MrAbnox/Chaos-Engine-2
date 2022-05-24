#ifndef COMPONENT_H
#define COMPONENT_H

//Forward Declaration
class GameObject;

class Component
{
public:
	explicit Component(GameObject* gameObject);
	virtual ~Component() = default;

	GameObject* getGameObject();
	void setGameObject(GameObject* gameObject);

	virtual void update(float deltaTime);

protected:
	GameObject* gameObject;

	friend class GameObject;
};

#endif