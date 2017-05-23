// Copyright 2017 Andy Taylor

#ifndef CHAMBER_H_INCLUDED
#define CHAMBER_H_INCLUDED

#include "Terrain.h"

#include <iostream>
#include <vector>

class Chamber : public Terrain {
 public:
    Chamber(){};
    Chamber(int worldX, int worldY, int worldZ, int width, int height, int length);

    void generateTerrain();
 private:

};


#endif  /* Chamber_H */
