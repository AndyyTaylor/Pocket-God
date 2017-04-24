// Copyright 2017 Andy Taylor
#include "Shader_Loader.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <GL/Glew.h>

extern std::string PROJECT_PATH;

namespace Shader {
std::string readFile(const char* file) {
    std::ifstream t(file);
    std::stringstream buffer;
    buffer << t.rdbuf();

    std::string fileContent = buffer.str();
    return fileContent;
}

void printShaderCompilationError(GLuint res) {
    int logLength;
    glGetShaderiv(res, GL_INFO_LOG_LENGTH, &logLength);

    char* shaderInfoLog = new char[logLength];
    glGetShaderInfoLog(res, logLength, &logLength, shaderInfoLog);

    std::cerr << shaderInfoLog << std::endl;
}

GLuint load_shader(const std::string &filename, GLenum type) {
    std::string str = readFile((PROJECT_PATH + filename).c_str());
    char* src = const_cast<char*>(str.c_str());

    int32_t size = str.length();
    GLuint res = glCreateShader(type);

    glShaderSource(res, 1, &src, &size);
    glCompileShader(res);

    int compile_ok = 0;
    glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
    if (compile_ok == 0) {
        std::cerr << "Shader failed to compile: " << std::endl;
        printShaderCompilationError(res);
        return 0;
    }

    return res;
}

GLuint load_program(const std::string &vfile, const std::string &ffile) {
    GLuint vs = load_shader(vfile, GL_VERTEX_SHADER);
    GLuint fs = load_shader(ffile, GL_FRAGMENT_SHADER);

    GLuint pid = glCreateProgram();
    glAttachShader(pid, vs);
    glAttachShader(pid, fs);

    glLinkProgram(pid);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return pid;
}
}   // namespace Shader
