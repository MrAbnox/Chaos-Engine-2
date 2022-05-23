#ifndef WINDOW_H
#define WINDOW_H

//#include<Windows.h>
#include <GLFW/glfw3.h>

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

	GLFWwindow* window;
	int screenWidth;
	int screenHeight;

private:
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif // !WINDOW_H