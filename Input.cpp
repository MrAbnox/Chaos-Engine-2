#include "Input.h"

Input* Input::instance()
{
	static Input* input = new Input;
	return input;
}


void cursor_input_callback(GLFWwindow* window, double posX, double posY) {

	// camera rotation
	static bool firstMouse = true;
	if (firstMouse)
	{
		lastX = (float)posX;
		lastY = (float)posY;
		firstMouse = false;
	}

	float xoffset = (float)posX - lastX;
	float yoffset = lastY - (float)posY; // reversed since y-coordinates go from bottom to top

	lastX = (float)posX;
	lastY = (float)posY;

	if (isPaused)
		return;

	// we use the handy camera class from LearnOpenGL to handle our camera
	camera.ProcessMouseMovement(xoffset, yoffset);
}