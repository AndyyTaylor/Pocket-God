// Copyright 2017 Andy Taylor

#include "Starting.h"

Starting::Starting(int worldX, int worldY, int width, int height, int length)
: Terrain(worldX, worldY, width, height, length) {
    // generateTerrain(width, height, length, bounds);
}

void Starting::generateTerrain() {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

    std::vector<float> bounds;
    addRectangle(&vertices, &uvs, 0, 0, 0, width, 0, length, bounds);
    addRectangle(&vertices, &uvs, 0, 0, 0, 0, height, length, bounds);
    addRectangle(&vertices, &uvs, width, 0, 0, 0, height, length, bounds);
    addRectangle(&vertices, &uvs, 0, height, 0, width, 0, length, bounds);
    addRectangle(&vertices, &uvs, 0, 0, length, width, height, 0, bounds);
    addRectangle(&vertices, &uvs, 0, 0, 0, width, height, 0, bounds);

    setupNormals(&normals, vertices);

    model.loadVertices(vertices, uvs, normals, "imgs/stone.jpg");

    model.entity.position.x = worldX;
    model.entity.position.z = worldY;  // Yeah i fucked up
}