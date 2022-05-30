#ifndef COMPONENT_H
#define COMPONENT_H

//Forward Declaration
class GameObject;

class Component
{
public:
	explicit Component(GameObject* gameObject);
	Component(const Component& c);
	virtual ~Component() = default;

	virtual void update() {};
	virtual void fixedUpdate(float deltaTime) {};
	
	GameObject* getGameObject();
	void setGameObject(GameObject& gameObject);

protected:
	GameObject* gameObject;

	friend class GameObject;
};

#endif