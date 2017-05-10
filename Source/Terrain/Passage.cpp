// Copyright 2017 Andy Taylor

#include "Passage.h"

Passage::Passage(int worldX, int worldY)
: Terrain(worldX, worldY) {
    generateTerrain();
}

void Passage::generateTerrain() {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;

    vertices.push_back(glm::vec3(0, 0, 100));
    vertices.push_back(glm::vec3(100, 0, 100));
    vertices.push_back(glm::vec3(0, 0, 0));

    vertices.push_back(glm::vec3(100, 0, 100));
    vertices.push_back(glm::vec3(100, 0, 0));
    vertices.push_back(glm::vec3(0, 0, 0));

    uvs.push_back(glm::vec2(0, 1));
    uvs.push_back(glm::vec2(1, 1));
    uvs.push_back(glm::vec2(0, 0));

    uvs.push_back(glm::vec2(1, 1));
    uvs.push_back(glm::vec2(1, 0));
    uvs.push_back(glm::vec2(0, 0));

    std::vector<glm::vec3> normals;

    for (int i = 0; i < vertices.size(); i+=3) {
        // std::cout << i << std::endl;
        glm::vec3 U = vertices[i+1] - vertices[i];
        glm::vec3 V = vertices[i+2] - vertices[i];

        glm::vec3 N;
        N.x = U.y * V.z - (U.z * V.y);
        N.y = U.z * V.x - (U.x * V.z);
        N.z = U.x * V.y - (U.y * V.x);

        normals.push_back(N);
        normals.push_back(N);
        normals.push_back(N);
    }

    model.loadVertices(vertices, uvs, normals, "imgs/grass4.png");

    model.entity.position.x = worldX;
    model.entity.position.z = worldY;  // Yeah i fucked up
}
