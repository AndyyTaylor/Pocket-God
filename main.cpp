#include <iostream>

#include "Source/Display.h"
#include "Source/Application.h"

#include <string>

std::string PROJECT_PATH;

int main(int argc, char* argv[])
{
	if (!Display::init())
		return -1;

	std::string s(argv[0]);
	PROJECT_PATH = s.substr(0, s.length()-5);
	std::cout << PROJECT_PATH << std::endl;
	Application app;
	app.runMainGameLoop();

	std::cout << "Hello World" << std::endl;
	return 0;
}
