#include "Window.h"


#include <iostream>
//namespace callbacks
//{

	void cursor_input_callback(GLFWwindow* window, double posX, double posY) {

		// camera rotation
		static bool firstMouse = true;
		float lastX = Window::instance()->getLastX();
		float lastY = Window::instance()->getLastY();

		if (firstMouse)
		{
			lastX = (float)posX;
			lastY = (float)posY;
			firstMouse = false;
		}

		float xOffset = (float)posX - lastX;
		float yOffset = lastY - (float)posY; // reversed since y-coordinates go from bottom to top

		lastX = (float)posX;
		lastY = (float)posY;

		Window::instance()->setLastX(lastX);
		Window::instance()->setLastY(lastY);

		if (Window::instance()->getIsPaused())
			return;

		// we use the handy camera class from LearnOpenGL to handle our camera
		//TODO:: Make Camera Process Mouse Movement

		std::cout << "XOFFSET: " + std::to_string(xOffset) + " YOFFSET: " + std::to_string(yOffset) << std::endl;
		Window::instance()->getCamera()->ProcessMouseMovement(xOffset, yOffset);
	}
	
	void key_input_callback(GLFWwindow* window, int button, int other, int action, int mods) {
		// controls pause mode
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			//isPaused = !isPaused;
			glfwSetInputMode(window, GLFW_CURSOR, Window::instance()->getIsPaused() ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
		}
	}

	// glfw: whenever the mouse scroll wheel scrolls, this callback is called
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		//camera.ProcessMouseScroll((float)yoffset);
		//TODO:: Add Scroll
	}

	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}


Window* Window::instance()
{
	static Window* window = new Window;
	return window;
}

void Window::initialize()
{
	//TODO:: Read values from previous 
	loadSettings();


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(screenWidth, screenHeight, "Exercise 9", NULL, NULL);
	if (window == NULL)
	{
		//std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_input_callback);
	glfwSetKeyCallback(window, key_input_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glDepthRange(-1, 1); // make the NDC a right handed coordinate system, with the camera pointing towards -z
	glEnable(GL_DEPTH_TEST); // turn on z-buffer depth test
	glDepthFunc(GL_LESS); // draws fragments that are closer to the screen in NDC

}

void Window::clear()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT );
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
	glfwPollEvents(); //Not sure if this is needed
}

void Window::setScreenSize(int& width, int& height)
{
}

void Window::setFullScreen(bool fullscreen)
{
	if (fullscreen)
		glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, 1920, 1080, GLFW_DONT_CARE);
	else
		glfwSetWindowMonitor(window, NULL, 0, 0, 1920, 1080, GLFW_DONT_CARE);
}

void Window::resetSettings()
{
	//TODO:: reset window settings
	//Use default file
}

void Window::saveSettings()
{
	//TODO:: Load last Save Settings
	//if there's no file already create new
	//otherwise overwrite current one
}

void Window::loadSettings()
{
	//TODO:: Read Settings

	//if there's no settings use default file
	screenHeight = 800;
	screenWidth = 1200;

	lastX = (float)screenWidth / 2.0;
	lastY = (float)screenHeight / 2.0;
}

bool Window::getIsPaused()
{
	return isPaused;
}

float Window::getLastX()
{
	return lastX;
}

float Window::getLastY()
{
	return lastY;
}

Camera* Window::getCamera()
{
	return camera;
}

GLFWwindow* Window::getWindow()
{
	return window;
}

glm::vec2 Window::getScreenSize()
{
	return  glm::vec2(screenWidth, screenHeight);
}

void Window::setCamera(Camera* camera)
{
	this->camera = camera;
}

void Window::setLastX(float x)
{
	lastX = x;
}

void Window::setLastY(float y)
{
	lastY = y;
}