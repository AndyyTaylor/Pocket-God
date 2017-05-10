// Copyright 2017 Andy Taylor
#include "Text.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>

Text::Text(int x2, int y2, int w, int h, std::string f) {  // HACK should be implicit initializer
    x = x2;
    y = y2;
    width = w;
    height = h;
    filename = f;
    type = 1;   // Global ENUM please!s

    vertices.push_back(glm::vec3(x+0, y+height, 0));
    vertices.push_back(glm::vec3(x+width, y+height, 0));
    vertices.push_back(glm::vec3(x+0, y+0, 0));


    vertices.push_back(glm::vec3(x+width, y+height, 0));
    vertices.push_back(glm::vec3(x+width, y+0, 0));
    vertices.push_back(glm::vec3(x+0, y+0, 0));


    uvs.push_back(glm::vec2(0, 1));
    uvs.push_back(glm::vec2(1, 1));
    uvs.push_back(glm::vec2(0, 0));

    uvs.push_back(glm::vec2(1, 1));
    uvs.push_back(glm::vec2(1, 0));
    uvs.push_back(glm::vec2(0, 0));

    setupBuffers();
}

void Text::setupBuffers() {
    GLuint pos_vbo;
    glGenBuffers(1, &pos_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3),
                 vertices.data(), GL_STATIC_DRAW);

    GLuint uv_vbo;
    glGenBuffers(1, &uv_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
    glBufferData(GL_ARRAY_BUFFER, uvs.size()*sizeof(glm::vec2),
            uvs.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_vao);
    bind();

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    SDL_Surface* Surface = IMG_Load(("/Data/fonts/" + filename).c_str());

    if (Surface == NULL) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);

    int Mode = GL_RGB;

    if (Surface->format->BytesPerPixel == 4) {
        Mode = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, Mode, Surface->w, Surface->h, 0, Mode, GL_UNSIGNED_BYTE,
                                                                          Surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unbind();
}
