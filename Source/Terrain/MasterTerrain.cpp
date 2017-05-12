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
    int r = rand() % 20;
    std::cout << r << std::endl;
    if (r > 0){ r = 0; } // Changed depending on how many possibilities I've created

    std::vector<float> bounds;
    switch(r) {
        case 0:
            bounds = {-1, -1, 0, 50, 0, 50};
            terrains.push_back(Starting(0, 0, 200, 200, 200, bounds));
            break;
        default:
            terrains.push_back(Starting(0, 0, 200, 200, 200, bounds));
            break;
    }
    //Starting s = Starting(0, 0, 200, 200, 200);

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
