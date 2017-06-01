// Copyright 2017 Andy Taylor

#ifndef MASTER_TERRAIN_H_INCLUDED
#define MASTER_TERRAIN_H_INCLUDED

#include "Terrain.h"

#include "../Camera.h"
#include "../Math/Matrix.h"
#include "../Shaders/Shader_Program.h"

#include <vector>
#include "Passage.h"

class MasterTerrain {
 public:
    MasterTerrain();

    void render(Shader::Shader_Program* simpleShader, Camera* camera);

    void generateDungeon();

    std::vector<Terrain>* getTerrains() { return &terrains; }

 private:
    std::vector<Terrain> terrains;

    void genStartingArea();
    Terrain genChamber(float worldX, float worldY, float worldZ, float rot, int depth);
    Terrain genPassage(float worldX, float worldY, float worldZ, float rot, int depth);

    float normang(float ang);
    
    void getModifiers(int* xmod, int* ymod, int* zmod, float rot);
    void getDimensions(float* width, float* height, float* length, float rot);
    void getModifiers2(int* xmod, int* ymod, int* zmod, float rot);
    void getModifiers3(int* xmod, int* ymod, int* zmod, float rot);

    int MAXDEPTH = 4;
};

#endif  /* MASTER_TERRAIN */
