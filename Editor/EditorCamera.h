#ifndef EDITORCAMERA_H
#define EDITORCAMERA_H

#include "Camera.h"

class EditorCamera : Camera
{
public:
	EditorCamera();
	~EditorCamera();

public:
	
	void update() override;
	void fixedUpdate(float deltaTime) override;

	void move();

private:

	GLfloat velocity;
	GLfloat sensitivity;
};

#endif // !EDITORCAMERA_H

