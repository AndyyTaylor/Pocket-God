#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Shaders/Shader_Program.h"
#include "Model.h"

class Application
{
public:
	Application();
	
	void runMainGameLoop();
	
private:
	Shader::Shader_Program shaderProgram;
	Model model;
};

#endif /* APPLICATION_H_ */
