#include "Application.h"

#include "Display.h"

Application::Application()
{
	
}

void Application::runMainGameLoop()
{
	while (!Display::checkForClose())
	{
		Display::clear();
		
		
		
		Display::update();
	}
	Display::close();
}
