// Copyright 2017 Andy Taylor
#include "MasterTerrain.h"

#include <cstdlib>
#include <ctime>

#include "Passage.h"
#include "Starting.h"
#include "../Camera.h"
#include "../Math/Matrix.h"
#include "../Shaders/Shader_Program.h"

MasterTerrain::MasterTerrain() {
    generateDungeon();
}

void MasterTerrain::generateDungeon() {
    srand((int) time(0));

    genStartingArea();

    //Starting s = Starting(0, 0, 200, 200, 200);
}

void MasterTerrain::genStartingArea() {
    // std::vector<float> bounds;
    int r = rand() % 20;
    if (r > 0){ r = 0; } // Changed depending on how many possibilities I've created

    Starting s;
    switch(r) {
        case 0:
        {
            // bounds = {-1, -1, 0, 50, 0, 50};
            s = Starting(0, 0, 200, 200, 200);

            s.generateTerrain();

            // s.addAdjTerrain(genPassage(100, 200));
            Terrain* p = genPassage(0, 0);
            p->model.entity.rotation = glm::vec3(0, 180, 0);
            s.addAdjTerrain(p);

            terrains.push_back(s);
            break;
        }
        default:
            // terrains.push_back(Starting(0, 0, 200, 200, 200));
            break;
    }
}

Terrain* MasterTerrain::genPassage(float worldX, float worldY) {
    int r = rand() % 20;
    if (r > 0){ r = 0; } // Changed depending on how many possibilities I've created

    Passage p;
    int index = 0;
    switch(r) {
        case 0:
        {
            p = Passage(worldX-50, worldY+200, 100, 100, 200);

            p.generateTerrain();

            index = terrains.size();
            terrains.push_back(p);
            break;
        }
        default:
            break;
    }

    return &terrains[index];
}

void MasterTerrain::render(Shader::Shader_Program* simpleShader, Camera* camera) {
    for (int i = 0; i < terrains.size(); i++) {
        glm::mat4 m = Maths::createModelMatrix(terrains[i].model.entity);
        glm::mat4 v = Maths::createViewMatrix(*camera);
        glm::mat4 mvp = Maths::createProjMatrix() * v * m;
        simpleShader->loadMVP(mvp, m, v);

        terrains[i].model.draw();
    }
}
