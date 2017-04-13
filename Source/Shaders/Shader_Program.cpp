#include "Shader_Program.h"
#include "Shader_Loader.h"

#include <iostream>
#include <string>
#include <GL/glew.h>

namespace Shader
{
Shader_Program::Shader_Program(const std::string &vertexShaderFile, const std::string &fragmentShaderFile)
: m_programId(load_program(vertexShaderFile, fragmentShaderFile))
{
	
}

void Shader_Program::bind()
{
	glUseProgram(m_programId);
}

void Shader_Program::unbind()
{
	glUseProgram(0);
}
}
