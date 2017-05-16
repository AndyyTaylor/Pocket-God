// Copyright 2017 Andy Taylor
#include "Model.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <vector>

extern std::string PROJECT_PATH;

namespace {
std::vector<GLfloat> points = {
    -0.5, -0.5, 0.5,
    -0.5, 0.5, -0.5,
    -0.5, 0.5, 0.5,
    -0.5, -0.5, 0.5,
    -0.5, 0.5, -0.5,
    -0.5, -0.5, -0.5,
    -0.5, 0.5, -0.5,
    0.5, -0.5, -0.5,
    0.5, 0.5, -0.5,
    -0.5, 0.5, -0.5,
    0.5, -0.5, -0.5,
    -0.5, -0.5, -0.5
};

std::vector<GLfloat> colors = {
    0.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0
};
}  // namespace

Model::Model() {
    entity.scale = glm::vec3(1.0, 1.0, 1.0);
    // entity.position = glm::vec3(0.0, -3.0, 3.0);
    // loadModel((PROJECT_PATH + "/Data/cup.obj").c_str());



    // entity.rotation.z = 1;
}

void Model::draw() {
    bind();
    // entity.rotation.y += 1;
    glBindTexture(GL_TEXTURE_2D, TextureID);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    unbind();
}

void Model::loadModel(const char * path) {
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    FILE * file = fopen(path, "r");
    if (file == NULL) {
        std::cerr << "Cannot open model file" << std::endl;
        return;
    }

    uint linesLoaded = 0;
    while (1) {
        char lineHeader[128];

        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF) break;

        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        } else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        } else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        } else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            /*int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d",
                                 &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                 &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                 &vertexIndex[2], &uvIndex[2], &normalIndex[2]);*/
            int matches = fscanf(file, "%d//%d %d//%d %d//%d",
                                &vertexIndex[0], &normalIndex[0],
                                &vertexIndex[1], &normalIndex[1],
                                &vertexIndex[2], &normalIndex[2]);

            if (matches != 6) {
                std::cerr << "File cannot be read by this obj parser" << std::endl;
                return;
            }

            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);

            /*uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);*/

            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
        linesLoaded++;
        // std::cout << "Loaded line: " << linesLoaded << std::endl;
    }
    std::cout << "Finished loading file." << std::endl;
    for (unsigned int i = 0; i < vertexIndices.size(); i++) {
        unsigned int vertexIndex = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[vertexIndex-1];
        vertices.push_back(vertex);

        // unsigned int uvIndex = uvIndices[i];
        // glm::vec2 uv = temp_vertices[uvIndex-1];
        // uvs.push_back(uv);

        unsigned int normalIndex = normalIndices[i];
        glm::vec3 normal = temp_normals[normalIndex-1];
        normals.push_back(normal);
    }
    std::cout << "Finished loadModel()" << std::endl;
}

void Model::loadVertices(std::vector<glm::vec3> v, std::vector<glm::vec2> u, std::vector<glm::vec3> n, std::string filename) {  // NOLINT
    vertices = v;
    uvs = u;
    normals = n;
    setupBuffers(filename);
    // std::cout << vertices.size() << std::endl << normals.size() << std::endl;
}

void Model::setupBuffers(std::string filename) {
    GLuint pos_vbo;
    glGenBuffers(1, &pos_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3),
                 vertices.data(), GL_STATIC_DRAW);

    GLuint norm_vbo;
    glGenBuffers(1, &norm_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, norm_vbo);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3),
                 normals.data(), GL_STATIC_DRAW);

    GLuint uv_vbo;
    glGenBuffers(1, &uv_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2),
                 uvs.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, norm_vbo);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    SDL_Surface* Surface = IMG_Load((PROJECT_PATH + "/Data/" + filename).c_str());

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
}

void Model::bind() {
    glBindVertexArray(m_vao);
}

void Model::unbind() {
    glBindVertexArray(0);
}
