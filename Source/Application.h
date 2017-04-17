#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Shaders/Shader_Program.h"
#include "EventHandler.h"
#include "Model.h"

class Application
{
public:
	Application();
	
	void input();
	void runMainGameLoop();
	
private:
	Shader::Shader_Program shaderProgram;
	Model model;
	EventHandler eventHandler;
};

#endif /* APPLICATION_H_ */
