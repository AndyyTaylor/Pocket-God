// Copyright 2017 Andy Taylor
#include "Rect.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>

Rect::Rect(int x2, int y2, int w, int h, glm::vec4 color) {  // HACK should be implicit initializer
    x = x2;
    y = y2;
    width = w;
    height = h;
    colour = color;
    type = 0;

    vertices.push_back(glm::vec3(x+0, y+height, 0.1));
    vertices.push_back(glm::vec3(x+width, y+height, 0.1));
    vertices.push_back(glm::vec3(x+0, y+0, 0.1));

    vertices.push_back(glm::vec3(x+width, y+height, 0.1));
    vertices.push_back(glm::vec3(x+width, y+0, 0.1));
    vertices.push_back(glm::vec3(x+0, y+0, 0.1));

    /*vertices.push_back(glm::vec2(0, 0.2));
    vertices.push_back(glm::vec2(1, 0.2));
    vertices.push_back(glm::vec2(0, 0));

    vertices.push_back(glm::vec2(1, 0.2));
    vertices.push_back(glm::vec2(1, 0));
    vertices.push_back(glm::vec2(0, 0));*/

    setupBuffers();
}

void Rect::setupBuffers() {
    GLuint pos_vbo;
    glGenBuffers(1, &pos_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3),
                 vertices.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_vao);
    bind();

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    unbind();
}
