// Copyright 2017 Andy Taylor
#include "Shader_Program.h"
#include "Shader_Loader.h"
#include "../Glm_common.h"

#include <iostream>
#include <string>
#include <GL/glew.h>

namespace Shader {
Shader_Program::Shader_Program(const std::string &vertexShaderFile,
                               const std::string &fragmentShaderFile)
: m_programId(load_program(vertexShaderFile, fragmentShaderFile)) {
    m_mvpLocation = glGetUniformLocation(m_programId, "MVP");
    m_mLocation = glGetUniformLocation(m_programId, "M");
    m_vLocation = glGetUniformLocation(m_programId, "V");
}

void Shader_Program::bind() {
    glUseProgram(m_programId);
}

void Shader_Program::unbind() {
    glUseProgram(0);
}

void Shader_Program::loadMVP(const glm::mat4 &matrix,
                             const glm::mat4 &mmatrix,
                             const glm::mat4 &vmatrix) {
    glUniformMatrix4fv(m_mvpLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    glUniformMatrix4fv(m_mLocation, 1, GL_FALSE, glm::value_ptr(mmatrix));
    glUniformMatrix4fv(m_vLocation, 1, GL_FALSE, glm::value_ptr(vmatrix));
}
}   // namespace Shader
