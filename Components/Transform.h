#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../Game/GameObject.h"
#include "Component.h"
#include <glm/matrix.hpp>

class Transform : public Component
{
public:

	explicit Transform(GameObject* object);
	virtual ~Transform() = default;

	void update() override {};
	void fixedUpdate(float deltaTime) override {};

public:

	void setPos();
	void setRot();
	void setScale();

public:

	void translate();
	void rotate();
	void scale();

public:

	void deleteChildren();
	int getChildrenCount();

	void setDirty(bool& value);
	void setParent(Transform& parent);

private:

	Transform* parent;
	GameObject* object;

private:

	bool isDirty;

	glm::vec3 up;
	glm::vec3 forward;
	glm::mat4 model;

};

#endif // !TRANSFORM_H