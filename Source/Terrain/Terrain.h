// Copyright 2017 Andy Taylor
#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include "../Model.h"
#include <SDL2/SDL.h>

class Terrain {
 public:
    static const int SIZE = 800;
    static const int VERTEX_COUNT = 256;
    static const int MAX_HEIGHT = 100;
    static const int MAX_PIXEL_COLOUR = 256*256*256;

    Terrain();

    // At some point I need to modify my code to allow me pass around 'references'
    // const Model& getModel(){ return m_model; }
    Model model;  // m_ for privates?
 private:
    SDL_Surface* img;
    int maxX, minX, maxY, minY;

    void getRGB(SDL_Surface* img, int x, int y, int* r2, int* g2, int* b2);
    void generateTerrain();
    float getHeight(int x, int y);
};


#endif  /* TERRAIN_H */
