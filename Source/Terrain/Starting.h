// Copyright 2017 Andy Taylor

#ifndef STARTING_H_INCLUDED
#define STARTING_H_INCLUDED

#include "Terrain.h"

#include <iostream>
#include <vector>

class Starting : public Terrain {
 public:
    Starting(int worldX, int worldY, int width, int height, int length, std::vector<float> bounds);

 private:
   void generateTerrain(int width, int height, int length, std::vector<float> bounds);
};


#endif  /* STARTING_H */
