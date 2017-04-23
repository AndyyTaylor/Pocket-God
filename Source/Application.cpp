#include "Application.h"

#include "Display.h"
#include "Glm_common.h"
#include "Math/Matrix.h"

#include <chrono>

Application::Application()
: shaderProgram("/Data/Shaders/vert.glsl", "/Data/Shaders/frag.glsl")
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

		float fps = 1000/getDelta();
		std::cout << fps << std::endl;
	}
	Display::close();
}

double Application::getDelta()
{
	auto currentTime = std::chrono::high_resolution_clock::now(); // I usually try not to use auto but the data type here is stupidly long
	std::chrono::duration<double> delta(currentTime-timePrev);

	timePrev = std::chrono::high_resolution_clock::now();

	return std::chrono::duration_cast<std::chrono::milliseconds>(delta).count();
}
