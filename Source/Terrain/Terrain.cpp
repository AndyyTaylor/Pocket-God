// Copyright 2017 Andy Taylor
#include "Terrain.h"

#include <iostream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "../Model.h"

extern std::string PROJECT_PATH;

Terrain::Terrain() {
    generateTerrain();
}

Uint32 get_pixel32(SDL_Surface *surface, int x, int y) {
    // Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    // Get the requested pixel
    return pixels[ ( y * surface->w ) + x ];
}

void Terrain::getRGB(SDL_Surface* img, int x, int y, int* r2, int* g2, int* b2) {
    SDL_LockSurface(img);
    Uint32 pixel = get_pixel32(img, x, y);
    Uint8 r, g, b;
    SDL_GetRGB(pixel, img->format, &r, &g, &b);
    SDL_UnlockSurface(img);
    if (x < minX) minX = x;
    if (x > maxX) maxX = x;
    if (y < minY) minY = y;
    if (y > maxY) maxY = y;
    *r2 = (int) r;
    *g2 = (int) g;
    *b2 = (int) b;
}

float Terrain::getHeight(int x, int y) {
    int r, g, b;
    int w = img->w;
    int h = img->h;
    getRGB(img, (float) x / (float) SIZE * w, (float) y / (float) SIZE * h, &r, &g, &b);
    float height = (r * g * b) / (float) MAX_PIXEL_COLOUR;
    height -= 0.5;
    height *= 2 * MAX_HEIGHT;
    //std::cout << height << std::endl;
    return height;
}

void Terrain::generateTerrain() {
    /*std::vector<glm::vec3> vertices = {
        glm::vec3(-1.0, 0.0, 1.0),
        glm::vec3(1.0, 0.0, 1.0),
        glm::vec3(-1.0, 0.0, -1.0),
        glm::vec3(-1.0, 0.0, -1.0),
        glm::vec3(1.0, 0.0, 1.0),
        glm::vec3(1.0, 0.0, -1.0)
    };*/

    std::vector<glm::vec3> vertices;

    img = IMG_Load((PROJECT_PATH + "/Data/heightmap.png").c_str());
    if (img == NULL) {
        std::cerr << "Failed to load image" << std::endl;
        return;
    }

    float s = (float) SIZE / (float) VERTEX_COUNT;
    float s2 = s/2;
    for (int y = 0; y < VERTEX_COUNT; y++) {
        for (int x = 0; x < VERTEX_COUNT; x++) {
            heights.push_back(getHeight((int) (x*s-s2), (int) (y*s+s2)));
            vertices.push_back(glm::vec3(x*s-s2, getHeight((int) (x*s-s2), (int) (y*s+s2)), y*s+s2));
            vertices.push_back(glm::vec3(x*s+s2, getHeight((int) (x*s+s2), (int) (y*s+s2)), y*s+s2));
            vertices.push_back(glm::vec3(x*s-s2, getHeight((int) (x*s-s2), (int) (y*s-s2)), y*s-s2));
            vertices.push_back(glm::vec3(x*s-s2, getHeight((int) (x*s-s2), (int) (y*s-s2)), y*s-s2));
            vertices.push_back(glm::vec3(x*s+s2, getHeight((int) (x*s+s2), (int) (y*s+s2)), y*s+s2));
            vertices.push_back(glm::vec3(x*s+s2, getHeight((int) (x*s+s2), (int) (y*s-s2)), y*s-s2));
        }
    }

    std::vector<glm::vec2> uvs;  // One day

    std::vector<glm::vec3> normals;

    for (int i = 0; i < vertices.size(); i+=3) {
        // std::cout << i << std::endl;
        glm::vec3 U = vertices[i+1] - vertices[i];
        glm::vec3 V = vertices[i+2] - vertices[i];

        glm::vec3 N;
        N.x = U.y * V.z - (U.z * V.y);
        N.y = U.z * V.x - (U.x * V.z);
        N.z = U.x * V.y - (U.y * V.x);

        normals.push_back(N);
        normals.push_back(N);
        normals.push_back(N);
    }

    /*std::cout << "MinX:\t" << minX << std::endl;
    std::cout << "MaxX:\t" << maxX << std::endl;
    std::cout << "MinY:\t" << minY << std::endl;
    std::cout << "MaxY:\t" << maxY << std::endl;*/
    std::cout << vertices.size() / 3 << std::endl;
    model.loadVertices(vertices, uvs, normals);
}

float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

float Terrain::getHeightAt(int x, int z) {
    float gridX = (float) x / (float) SIZE * VERTEX_COUNT;
    float gridZ = (float) z / (float) SIZE * VERTEX_COUNT;
    int index = floor(gridZ) * VERTEX_COUNT + floor(gridX);
    if (index < 0 || index >= heights.size()) return 0;

    glm::vec3 p1, p2, p3;
    float height;
    if (gridX-floor(gridX) < 1 - (gridZ-floor(gridZ))) {
        height = barryCentric(glm::vec3(0, heights[index], 0),
                              glm::vec3(1, heights[index+1], 0),
                              glm::vec3(0, heights[index+VERTEX_COUNT], 1),
                              glm::vec2(gridX-floor(gridX), gridZ-floor(gridZ)));
        //height = 40;
    } else {
        height = barryCentric(glm::vec3(1, heights[index+1], 0),
                              glm::vec3(1, heights[index+1+VERTEX_COUNT], 1),
                              glm::vec3(0, heights[index+VERTEX_COUNT], 1),
                              glm::vec2(gridX-floor(gridX), gridZ-floor(gridZ)));

    }


    //std::cout << gridX-floor(gridX) << ", " << gridZ-floor(gridZ) << std::endl;
    return height;
}
