#ifndef CAMERA_H
#define CAMERA_H

#include "Components/Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include "../Game/Shader.h"

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
class Camera : public Component
{
public:
	explicit Camera(GameObject* gameObject);
	
public:	

	virtual void update() {};
	virtual void fixedUpdate(float deltaTime) {};
	void render();

private:
	
	void setDefault(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

public:
	
	void sendData(Shader& shader);

private:
	void updateCameraVectors();
	glm::mat4 getViewMatrix();
	
public:
	
	void SetPos(float x, float y, float z);
	void SetRot(float x, float y, float z);
	enum class Origin2D { TOP_LEFT, BOTTOM_LEFT };

	void SetOrthoView(Origin2D origin = Origin2D::BOTTOM_LEFT);
	void SetPerspView(GLfloat nearClip = 0.1f, GLfloat farClip = 1000.0f);
	void SetProjection(const glm::mat4& projRef);
	
	glm::mat4 GetProjection();
	glm::mat4 GetView();

	//TODO:: Add Later (Not important) & add vector overloads
	/*void SetLookAt(float x, float y, float z, float targetX, float targetY, float targetZ, float upX, float upY, float upZ);
	void SetLookAt(float x, float y, float z, float targetX, float targetY, float targetZ);
	void SetLookAt(float x, float y, float z, float targetX, float targetY, float targetZ, float upX, float upY, float upZ, float roll);
	void SetLookAt(float x, float y, float z, float targetX, float targetY, float targetZ, float upX, float upY, float upZ);
	void SetLookAt(float x, float y, float z, float targetX, float targetY, float targetZ, float upX, float upY, float upZ, float roll, float pitch, float yaw);
	void SetLookAt(float x, float y, float z, float targetX, float targetY, float targetZ, float upX, float upY, float upZ, float roll, float pitch, float yaw, float roll2, float pitch2, float yaw2);
	void SetLookAt(float x, float y, float z, float targetX, float targetY, float targetZ, float upX, float upY, float upZ, float roll, float pitch, float yaw, float roll2, float pitch2, float yaw2, float roll3, float pitch3, float yaw3);*/

protected:



	const GLfloat FOV = 45.0f;
	const GLfloat NEAR_CLIP = 0.1f;
	const GLfloat FAR_CLIP = 1000.0f;

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 worldUp;
	glm::vec3 right;

	float yaw;
	float pitch;
	float zoom;

	glm::mat4 view;
	glm::mat4 proj;
	glm::mat4 viewProj;
};

#endif
