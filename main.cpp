#include "Application/Application.h"

#include <iostream>
//-------------------------------------------------------------------------------
//Main
//-------------------------------------------------------------------------------
int main(int argc, char* args[])
{
	Application::instance()->run();

	return 0;
}