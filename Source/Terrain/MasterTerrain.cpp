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
    float width, height, length;
    switch(r) {
        case 0:
        {
            // bounds = {-1, -1, 0, 50, 0, 50};
            width = 200; height = 200; length = 200;
            s = Starting(0, 0, 0, width, height, length);

            s.generateTerrain();

            // s.addAdjTerrain(genPassage(100, 200));
            s.addAdjTerrain(genPassage(0, -height/2, length/2, 1, 1, 1));
            Terrain* p = genPassage(0, -height/2, -length/2, 1, 1, -1);
            p->model.entity.rotation.y = 180;
            s.addAdjTerrain(p);

            p = genPassage(width/2, -height/2, 0, 1, 1, 1);
            p->model.entity.rotation.y = 90;
            s.addAdjTerrain(p);

            // p = genPassage(0, 0);
            // p->model.entity.rotation = glm::vec3(0, 90, 0);

            terrains.push_back(s);
            break;
        }
        default:
            // terrains.push_back(Starting(0, 0, 200, 200, 200));
            break;
    }
}

Terrain* MasterTerrain::genPassage(float worldX, float worldY, float worldZ, int xmod, int ymod, int zmod) {
    int r = rand() % 20;
    if (r > 0){ r = 0; } // Changed depending on how many possibilities I've created

    Passage p;
    int index = 0;
    float width, height, length;
    switch(r) {
        case 0:
        {
            width = 100; height = 100; length = 500;
            p = Passage(worldX+xmod*width/2, worldY+height/2*ymod, worldZ+zmod*length/2, width, height, length);

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
