#include "Application.h"

#include "Display.h"
#include "Glm_common.h"
#include "Math/Matrix.h"

Application::Application()
: shaderProgram("Data/Shaders/vert.glsl", "Data/Shaders/frag.glsl")
{
	
}

void Application::runMainGameLoop()
{
	while (Display::isOpen()) // !Display::checkForClose()
	{
		Display::clear();
		shaderProgram.bind();
		
		eventHandler.input(&model);
		
		glm::mat4 m = Maths::createModelMatrix(model.entity);
		glm::mat4 v = Maths::createViewMatrix();
		glm::mat4 mvp = Maths::createProjMatrix() * v * m;
		shaderProgram.loadMVP(mvp, m, v);
		
		model.draw();
		
		shaderProgram.unbind();
		Display::update();
	}
	Display::close();
}

