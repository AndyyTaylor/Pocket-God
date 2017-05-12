// Copyright 2017 Andy Taylor

#ifndef MASTER_TERRAIN_H_INCLUDED
#define MASTER_TERRAIN_H_INCLUDED

#include "Terrain.h"

#include "../Camera.h"
#include "../Math/Matrix.h"
#include "../Shaders/Shader_Program.h"

#include <vector>

class MasterTerrain {
 public:
    MasterTerrain();

    void render(Shader::Shader_Program* simpleShader, Camera* camera);

    void generateDungeon();

    std::vector<Terrain>* getTerrains() { return &terrains; }

 private:
    std::vector<Terrain> terrains;
};

#endif  /* MASTER_TERRAIN */
