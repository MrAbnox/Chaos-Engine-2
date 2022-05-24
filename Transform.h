#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "GameObject.h"

class Transform
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

};

#endif // !TRANSFORM_H