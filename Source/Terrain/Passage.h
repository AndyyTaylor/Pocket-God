// Copyright 2017 Andy Taylor

#ifndef PASSAGE_H_INCLUDED
#define PASSAGE_H_INCLUDED

#include "Terrain.h"

#include <iostream>

class Passage : public Terrain {
 public:
    Passage(int worldX, int worldY, int width, int height, int length);

 private:
   void generateTerrain(int width, int height, int length);

};


#endif  /* PASSAGE_H */
