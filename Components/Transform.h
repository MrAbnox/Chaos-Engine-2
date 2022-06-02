#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../Game/GameObject.h"
#include "Component.h"
#include <glm/matrix.hpp>
#include "../Game/Shader.h"

class Transform : public Component
{
public:

	explicit Transform(GameObject* object);
	virtual ~Transform() = default;

	void update() override {};
	void fixedUpdate(float deltaTime) override {};
	void sendData(Shader& shader);

public:

	//glm::vec3 getPos();
	glm::mat4* getModel();
	void setPos(glm::vec3 pos);
	void setRot(glm::vec3 rot);
	void setScale(glm::vec3 scale);

public:

	void translate(glm::vec3 pos);
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

	glm::vec3 position;
	glm::vec3 sl;
	glm::vec3 up;
	glm::vec3 forward;
	glm::mat4 model;

};

#endif // !TRANSFORM_H