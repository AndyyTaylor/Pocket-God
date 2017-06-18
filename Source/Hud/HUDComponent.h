// Copyright 2017 Andy Taylor
#ifndef HUD_COMPONENT_H_INCLUDED
#define HUD_COMPONENT_H_INCLUDED

#include <GL/glew.h>
#include <vector>

#include "../Glm_common.h"


class HUDComponent {
 public:
    void draw();

    void bind() { glBindVertexArray(m_vao); }
    void unbind() { glBindVertexArray(0); }
    GLuint type;

    glm::vec4 getColour(){ return colour; }
    void loadText(std::string txt, std::string filename);

 protected:
    GLuint m_vao;
    GLuint TextureID;
    float x, y, width, height;
    glm::vec4 colour;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
};


#endif /* HUDComponent */
