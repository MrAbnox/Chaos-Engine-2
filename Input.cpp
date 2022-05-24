#include "Input.h"

Input* Input::instance()
{
	static Input* input = new Input;
	return input;
}
