// Copyright 2017 Andy Taylor

#include "Passage.h"

Passage::Passage(int worldX, int worldY, int worldZ, int width, int height, int length)
: Terrain(worldX, worldY, worldZ, width, height, length) {
    // generateTerrain(width, height, length);
}

void Passage::generateTerrain() {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

    addRectangle(&vertices, &uvs, 0, 0, 0, width, 0, length, width, height, length);
    addRectangle(&vertices, &uvs, 0, 0, 0, 0, height, length, width, height, length);
    addRectangle(&vertices, &uvs, width, 0, 0, 0, height, length, width, height, length);
    addRectangle(&vertices, &uvs, 0, height, 0, width, 0, length, width, height, length);

    setupNormals(&normals, vertices);

    model.loadVertices(vertices, uvs, normals, "imgs/stone.jpg");

    model.entity.position.x = worldX;
    model.entity.position.y = worldY;
    model.entity.position.z = worldZ;
}
