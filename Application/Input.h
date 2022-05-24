#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

class Input
{

private:

	Input() {}
	Input(const Input&);
	Input& operator = (Input&);

public:

	static Input* instance();
};

#endif