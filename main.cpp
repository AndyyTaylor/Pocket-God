#include <iostream>

#include "Source/Display.h"
#include "Source/Application.h"

int main(int argc, char* argv[])
{
	if (!Display::init())
		return -1;
	
	Application app;
	app.runMainGameLoop();
	
	std::cout << "Hello World" << std::endl;
	return 0;
}

