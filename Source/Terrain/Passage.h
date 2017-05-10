// Copyright 2017 Andy Taylor

#ifndef PASSAGE_H_INCLUDED
#define PASSAGE_H_INCLUDED

#include "Terrain.h"

#include <iostream>

class Passage : public Terrain {
 public:
    Passage(int worldX, int worldY);

 private:
    void generateTerrain();
};


#endif  /* PASSAGE_H */
