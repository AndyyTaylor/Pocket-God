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

Terrain::Terrain(int worldX, int worldY)
: worldX(worldX)
, worldY(worldY) {

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
/*
void Terrain::generateTerrain() {
    // std::vector<glm::vec3> vertices = {
    //     glm::vec3(-1.0, 0.0, 1.0),
    //     glm::vec3(1.0, 0.0, 1.0),
    //     glm::vec3(-1.0, 0.0, -1.0),
    //     glm::vec3(-1.0, 0.0, -1.0),
    //     glm::vec3(1.0, 0.0, 1.0),
    //     glm::vec3(1.0, 0.0, -1.0)
    // };

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;

    img = IMG_Load((PROJECT_PATH + "/Data/imgs/heightmap.png").c_str());
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

            float xoff = (float) ((int) x % (int) div)/div, yoff = (float) ((int) y % (int) div)/div;
            uvs.push_back(glm::vec2(xoff, yoff+1/div));
            uvs.push_back(glm::vec2(xoff+1/div, yoff+1/div));
            uvs.push_back(glm::vec2(xoff, yoff));
            uvs.push_back(glm::vec2(xoff, yoff));
            uvs.push_back(glm::vec2(xoff+1/div, yoff+1/div));
            uvs.push_back(glm::vec2(xoff+1/div, yoff));
        }
    }



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

    // std::cout << "MinX:\t" << minX << std::endl;
    // std::cout << "MaxX:\t" << maxX << std::endl;
    // std::cout << "MinY:\t" << minY << std::endl;
    // std::cout << "MaxY:\t" << maxY << std::endl;
    // std::cout << vertices.size() / 3 << std::endl;
    model.loadVertices(vertices, uvs, normals, "imgs/grass4.png");

    model.entity.position.x = worldX;
    model.entity.position.z = worldY;  // Yeah i fucked up
}
*/
float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

void Terrain::setupNormals(std::vector<glm::vec3>* normals, std::vector<glm::vec3> vertices) {
    for (int i = 0; i < vertices.size(); i+=3) {
        // std::cout << i << std::endl;
        glm::vec3 U = vertices[i+1] - vertices[i];
        glm::vec3 V = vertices[i+2] - vertices[i];

        glm::vec3 N;
        N.x = U.y * V.z - (U.z * V.y);
        N.y = U.z * V.x - (U.x * V.z);
        N.z = U.x * V.y - (U.y * V.x);

        normals->push_back(N);
        normals->push_back(N);
        normals->push_back(N);
    }
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
        // height = 40;
    } else {
        height = barryCentric(glm::vec3(1, heights[index+1], 0),
                              glm::vec3(1, heights[index+1+VERTEX_COUNT], 1),
                              glm::vec3(0, heights[index+VERTEX_COUNT], 1),
                              glm::vec2(gridX-floor(gridX), gridZ-floor(gridZ)));
    }


    // std::cout << gridX-floor(gridX) << ", " << gridZ-floor(gridZ) << std::endl;
    return height;
}

void Terrain::updateDiv(float d) {
    div += d;
    // generateTerrain();
}

void Terrain::addRectangle(std::vector<glm::vec3>* vertices, std::vector<glm::vec2>* uvs, float x, float y, float z, float w, float h, float l) {
    std::vector<float> bounds;
    addRectangle(vertices, uvs, x, y, z, w, h, l, bounds);
}

void Terrain::addRectangle(std::vector<glm::vec3>* vertices, std::vector<glm::vec2>* uvs, float x, float y, float z, float w, float h, float l, std::vector<float> bounds) {
    float div = 30;
    int xmod = fmin(w/div, 1);
    int ymod = fmin(h/div, 1);
    int zmod = fmin(l/div, 1);
    for (int dx = 0; dx < fmax(w/div, 1); dx++) {
        for (int dy = 0; dy < fmax(h/div, 1); dy++) {
            for (int dz = 0; dz < fmax(l/div, 1); dz++) {
                float x2 = x + dx*(div);
                float y2 = y + dy*(div);
                float z2 = z + dz*(div);

                bool skip = false;
                for (int b = 0; b < bounds.size() / 6; b++) {
                    if ((bounds[b+0] == -1 || (bounds[b+0] < x2 && x2 < bounds[b+1]))
                        && (bounds[b+2] == -1 || (bounds[b+2] < y2 && y2 < bounds[b+3]))
                        && (bounds[b+4] == -1 || (bounds[b+4] < z2 && z2 < bounds[b+5]))
                    ) {
                        skip = true;
                    }
                }
                if (skip) continue;


                // Doesn't work for width / height rectangles
                    // Is it possible to keep it with the same code?
                    // Or do I need a separate case
                vertices->push_back(glm::vec3(x2, y2+div*ymod, z2+div*zmod));
                vertices->push_back(glm::vec3(x2+div*xmod, y2, z2+div*zmod));
                vertices->push_back(glm::vec3(x2, y2+div*ymod, z2));

                vertices->push_back(glm::vec3(x2+div*xmod, y2, z2+div*zmod));
                vertices->push_back(glm::vec3(x2+div*xmod, y2, z2));
                vertices->push_back(glm::vec3(x2, y2+div*ymod, z2));

                uvs->push_back(glm::vec2(0, 1));
                uvs->push_back(glm::vec2(1, 1));
                uvs->push_back(glm::vec2(0, 0));

                uvs->push_back(glm::vec2(1, 1));
                uvs->push_back(glm::vec2(1, 0));
                uvs->push_back(glm::vec2(0, 0));
            }
        }
    }
}
