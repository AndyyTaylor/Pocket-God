// Copyright 2017 Andy Taylor

#include "Passage.h"

Passage::Passage(int worldX, int worldY, int width, int height, int length)
: Terrain(worldX, worldY) {
    generateTerrain(width, height, length);
}

void Passage::generateTerrain(int width, int height, int length) {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

    addRectangle(&vertices, &uvs, 0, 0, 0, 120, 0, 500);
    addRectangle(&vertices, &uvs, 0, 0, 0, 0, 120, 500);
    addRectangle(&vertices, &uvs, 120, 0, 0, 0, 120, 500);
    addRectangle(&vertices, &uvs, 0, 120, 0, 120, 0, 500);

    setupNormals(&normals, vertices);

    model.loadVertices(vertices, uvs, normals, "imgs/stone.jpg");

    model.entity.position.x = worldX;
    model.entity.position.z = worldY;  // Yeah i fucked up
}
