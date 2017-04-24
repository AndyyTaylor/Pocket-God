// Copyright 2017 Andy Taylor
#ifndef SHADER_LOADER_H_
#define SHADER_LOADER_H_

#include <string>
#include <GL/glew.h>

namespace Shader {
GLuint load_shader(const std::string &filename, GLenum type);
GLuint load_program(const std::string &vfile, const std::string &ffile);
}

#endif /* SHADER_LOADER_H_ */
