#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../Editor/Camera.h"


class Window
{
private:

	Window() {}
	Window(const Window&);
	Window& operator = (Window&);

public:

	static Window* instance();

	void initialize();
	void clear();
	void swapBuffers();
	void setScreenSize(int& width, int& height);

private:

	void setFullScreen(bool fullscreen); //TODO:: Add this function

private:

	void resetSettings();
	void saveSettings();
	void loadSettings();

public:
	
	bool getIsPaused();

	float getLastX();
	float getLastY();

	Camera* getCamera();
	GLFWwindow* getWindow();
	glm::vec2 getScreenSize();

	void setCamera(Camera* camera);
	//TODO:: Pass as Reference
	void setLastX(float x);
	void setLastY(float y);


private:

	Camera* camera;
	GLFWwindow* window;
	int screenWidth;
	int screenHeight;

	float lastX;
	float lastY;

	bool isPaused = false;
};

#endif // !WINDOW_H