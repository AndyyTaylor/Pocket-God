#ifndef SHADER_PROGRAM_H_
#define SHADER_PROGRAM_H_

#include <string>
#include <GL/glew.h>

namespace Shader
{
class Shader_Program
{
public:
	Shader_Program(const std::string &vertexShaderFile, const std::string &fragmentShaderFile);
	
	void bind();
	void unbind();

private:
	GLuint m_programId;
};
}

#endif /* SHADER_PROGRAM_H_ */
