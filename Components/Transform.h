#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "GameObject.h"
#include "Component.h"
#include <glm/matrix.hpp>

class Transform : Component
{
public:

	Transform(GameObject* object);
	~Transform();

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

};

#endif // !TRANSFORM_H