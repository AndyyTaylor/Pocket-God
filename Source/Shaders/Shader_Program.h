// Copyright 2017 Andy Taylor
#ifndef SHADER_PROGRAM_H_
#define SHADER_PROGRAM_H_

#include <string>
#include <GL/glew.h>
#include "../Glm_common.h"

namespace Shader {
class Shader_Program {
 public:
    Shader_Program(const std::string &vertexShaderFile, const std::string &fragmentShaderFile);

    void bind();
    void unbind();

    void loadMVP(const glm::mat4 &matrix, const glm::mat4 &mmatrix, const glm::mat4 &vmatrix);

 private:
    GLuint m_programId;
    GLuint m_mvpLocation;
    GLuint m_mLocation;
    GLuint m_vLocation;
};
}   // namespace Shader

#endif /* SHADER_PROGRAM_H_ */
