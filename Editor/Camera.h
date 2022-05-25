#ifndef CAMERA_H
#define CAMERA_H

#include "Components/Component.h"
#include <glm/matrix.hpp>
#include <glad/glad.h>

class Camera : Component
{
public:
	Camera();
	~Camera();
	
public:	


	virtual void update() {};
	virtual void fixedUpdate(float deltaTime) {};
	
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	
public:

	enum class Origin2D { TOP_LEFT, BOTTOM_LEFT };

	void SetOrthoView(Origin2D origin = Origin2D::BOTTOM_LEFT);
	void SetPerspView(GLfloat nearClip = 0.1f, GLfloat farClip = 1000.0f);
	void SetProjection(const glm::mat4& projRef);
	
	glm::mat4 GetProjection();
	glm::mat4 GetView();

	void SetProjection(float fov, float aspect, float near, float far);
	void SetViewport(float x, float y, float width, float height);
	void SetPerspective(float fov, float aspect, float near, float far);
	void SetOrthographic(float left, float right, float bottom, float top, float near, float far);

	
	//TODO:: Add Later (Not important) & add vector overloads
	void SetLookAt(float x, float y, float z, float targetX, float targetY, float targetZ, float upX, float upY, float upZ);
	void SetLookAt(float x, float y, float z, float targetX, float targetY, float targetZ);
	void SetLookAt(float x, float y, float z, float targetX, float targetY, float targetZ, float upX, float upY, float upZ, float roll);
	void SetLookAt(float x, float y, float z, float targetX, float targetY, float targetZ, float upX, float upY, float upZ);
	void SetLookAt(float x, float y, float z, float targetX, float targetY, float targetZ, float upX, float upY, float upZ, float roll, float pitch, float yaw);
	void SetLookAt(float x, float y, float z, float targetX, float targetY, float targetZ, float upX, float upY, float upZ, float roll, float pitch, float yaw, float roll2, float pitch2, float yaw2);
	void SetLookAt(float x, float y, float z, float targetX, float targetY, float targetZ, float upX, float upY, float upZ, float roll, float pitch, float yaw, float roll2, float pitch2, float yaw2, float roll3, float pitch3, float yaw3);

protected:

	const GLfloat FOV = 45.0f;
	const GLfloat NEAR_CLIP = 0.1f;
	const GLfloat FAR_CLIP = 1000.0f;

	glm::mat4 view;
	glm::mat4 proj;
};

#endif
