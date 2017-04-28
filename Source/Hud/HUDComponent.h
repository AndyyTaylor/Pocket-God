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
 protected:
    GLuint m_vao;
    GLuint TextureID;
    
    float x, y, width, height;

    std::vector<glm::vec2> vertices;
};


#endif /* HUDComponent */
