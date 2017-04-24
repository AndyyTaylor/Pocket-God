#include "Terrain.h"

#include <iostream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "../Model.h"

extern std::string PROJECT_PATH;

Terrain::Terrain()
{
    generateTerrain();
}

Uint32 get_pixel32( SDL_Surface *surface, int x, int y )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Get the requested pixel
    return pixels[ ( y * surface->w ) + x ];
}

void getRGB(SDL_Surface* img, int x, int y, int* r2, int* g2, int* b2)
{
    SDL_LockSurface(img);
    Uint32 pixel = get_pixel32(img, x, y);
    Uint8 r, g, b;
    Uint8 t = 10;
    SDL_GetRGB(pixel, img->format, &r, &g, &b);
    SDL_UnlockSurface(img);

    *r2 = (int) r;
    *g2 = (int) g;
    *b2 = (int) b;
}

void Terrain::generateTerrain()
{
    /*std::vector<glm::vec3> vertices = {
        glm::vec3(-1.0, 0.0, 1.0),
        glm::vec3(1.0, 0.0, 1.0),
        glm::vec3(-1.0, 0.0, -1.0),
        glm::vec3(-1.0, 0.0, -1.0),
        glm::vec3(1.0, 0.0, 1.0),
        glm::vec3(1.0, 0.0, -1.0)
    };*/

    std::vector<glm::vec3> vertices;

    SDL_Surface* img = IMG_Load((PROJECT_PATH + "/Data/heightmap.png").c_str());
    if (img == NULL)
    {
        std::cerr << "Failed to load image" << std::endl;
    }

    int r, g, b;
    int w = img->w;
    int h = img->h;

    std::cout << "r: " << (int) r << "\tg: " << (int) g << "\tb: " << (int) b << std::endl;

    float s = (float) SIZE / (float) VERTEX_COUNT;
    float s2 = s/2;
    for (int x = 0; x < VERTEX_COUNT; x++)
    {
        for (int y = 0; y < VERTEX_COUNT; y++)
        {
            getRGB(img, (float) x / (float) VERTEX_COUNT * w, (float) y / (float) VERTEX_COUNT * h, &r, &g, &b);
            float vh = (float) r / 128.0f;
            vh = 0;
            std::cout << "r: " << (int) r << "\tg: " << (int) g << "\tb: " << (int) b << "\th: " << vh << std::endl;
            vertices.push_back(glm::vec3(x*s-s2, vh, y*s+s2));
            vertices.push_back(glm::vec3(x*s+s2, vh, y*s+s2));
            vertices.push_back(glm::vec3(x*s-s2, vh, y*s-s2));
            vertices.push_back(glm::vec3(x*s-s2, vh, y*s-s2));
            vertices.push_back(glm::vec3(x*s+s2, vh, y*s+s2));
            vertices.push_back(glm::vec3(x*s+s2, vh, y*s-s2));
        }
    }

    std::vector<glm::vec2> uvs; // One day

    std::vector<glm::vec3> normals;

    for (int i = 0; i < vertices.size(); i+=3)
    {
        //std::cout << i << std::endl;
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

    model.loadVertices(vertices, uvs, normals);
}
