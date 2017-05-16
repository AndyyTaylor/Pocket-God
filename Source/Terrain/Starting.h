// Copyright 2017 Andy Taylor

#ifndef STARTING_H_INCLUDED
#define STARTING_H_INCLUDED

#include "Terrain.h"

#include <iostream>
#include <vector>

class Starting : public Terrain {
 public:
    Starting(){};
    Starting(int worldX, int worldY, int worldZ, int width, int height, int length);

    void generateTerrain();
 private:

};


#endif  /* STARTING_H */
