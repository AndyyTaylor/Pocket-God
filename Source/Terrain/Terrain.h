// Copyright 2017 Andy Taylor
#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include "../Model.h"
#include <SDL2/SDL.h>
#include <vector>

class Terrain {
 public:
    static const int SIZE = 800;
    static const int VERTEX_COUNT = 128;
    static const int MAX_HEIGHT = 200;
    static const int MAX_PIXEL_COLOUR = 256*256*256;

    Terrain(int worldX, int worldY);

    float getHeightAt(int x, int z);

    // At some point I need to modify my code to allow me pass around 'references'
    // const Model& getModel(){ return m_model; }
    Model model;  // m_ for privates?

    void updateDiv(float d);

 private:
    SDL_Surface* img;
    int worldX, worldY;
    int maxX, minX, maxY, minY;
    float div = 20;

    std::vector<float> heights;

    void getRGB(SDL_Surface* img, int x, int y, int* r2, int* g2, int* b2);
    void generateTerrain();
    float getHeight(int x, int y);
};


#endif  /* TERRAIN_H */
