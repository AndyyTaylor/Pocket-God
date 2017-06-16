// Copyright 2017 Andy Taylor
#include "Text.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>

Text::Text(int x2, int y2, int width, int height, std::string txt, std::string f) {  // HACK should be implicit initializer
    x = x2;
    y = y2;
    filename = f;
    type = 1;   // Global ENUM please!
    
    std::string characters = {" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxy"};
    //{" ", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ";", "<", "=", ">", "?", "@", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "[", "\\", "]", "^", "_", "`", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y"};
    for (int i = 0; i < txt.size(); i++) {
        int ind = -1;
        for (int index = 0; index < characters.size(); index++) {
            if (characters[index] == txt[i]) {
                ind = index;
                break;
            }
        }
        if (ind == -1) {
            std::cout << "Can;t read text" << std::endl;
            return;
        }

        vertices.push_back(glm::vec3(x+width*i, y+height*(1), 0));
        vertices.push_back(glm::vec3(x+width*(i+1), y+height*(1), 0));
        vertices.push_back(glm::vec3(x+width*i, y+0, 0));

        vertices.push_back(glm::vec3(x+width*(i+1), y+height*(1), 0));
        vertices.push_back(glm::vec3(x+width*(i+1), y+0, 0));
        vertices.push_back(glm::vec3(x+width*i, y+0, 0));
        
        //ind = 1;
        float xuv = (int) (ind % 10);
        float yuv = (int) (ind/10);
        float xtrim = 0.02;
        float ytrim = 0.03;
        std::cout << xuv << ", " << yuv << std::endl;
        uvs.push_back(glm::vec2(0.1 * xuv + xtrim + 0.01, 0.111 * (yuv + 1) - ytrim));
        uvs.push_back(glm::vec2(0.1 * (xuv + 1) - xtrim, 0.111 * (yuv + 1) - ytrim));
        uvs.push_back(glm::vec2(0.1 * xuv + xtrim + 0.01, 0.111 * yuv));

        uvs.push_back(glm::vec2(0.1 * (xuv + 1) - xtrim, 0.111 * (yuv + 1) - ytrim));
        uvs.push_back(glm::vec2(0.1 * (xuv + 1) - xtrim, 0.111 * yuv));
        uvs.push_back(glm::vec2(0.1 * xuv + xtrim + 0.01, 0.111  * (yuv)));
    }
    

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
        std::cerr << "Failed to load image" << std::endl;
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
