#include "Application.h"

#include "Display.h"

Application::Application()
: shaderProgram("Data/Shaders/vert.glsl", "Data/Shaders/frag.glsl")
{
	
}

void Application::runMainGameLoop()
{
	while (!Display::checkForClose())
	{
		Display::clear();
		shaderProgram.bind();
		
		model.draw();
		
		shaderProgram.unbind();
		Display::update();
	}
	Display::close();
}
