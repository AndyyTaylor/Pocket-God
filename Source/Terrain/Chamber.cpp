// Copyright 2017 Andy Taylor

#include "Chamber.h"

Chamber::Chamber(int worldX, int worldY, int worldZ, int width, int height, int length)
: Terrain(worldX, worldY, worldZ, width, height, length) {
    // generateTerrain(width, height, length, bounds);
}

void Chamber::generateTerrain() {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    
    std::cout << adjacent.size() << std::endl;
    std::vector<float> bounds;
    for (int i = 0; i < adjacent.size(); i++) {
        std::cout << adjacent[i].self_bounds.size() << std::endl;
        std::cout << "2" << std::endl;
        for (int l = 0; l < adjacent[i].self_bounds.size(); l++) {
            std::cout << "Add 1" << std::endl;
            bounds.push_back(adjacent[i].self_bounds[l]);
        }
    }
    std::cout << "Bounds: " << bounds.size() << std::endl;
    
    addRectangle(&vertices, &uvs, 0, 0, 0, width, 0, length, width, height, length, bounds);
    addRectangle(&vertices, &uvs, 0, 0, 0, 0, height, length, width, height, length, bounds);
    addRectangle(&vertices, &uvs, width, 0, 0, 0, height, length, width, height, length, bounds);
    addRectangle(&vertices, &uvs, 0, height, 0, width, 0, length, width, height, length, bounds);
    addRectangle(&vertices, &uvs, 0, 0, length, width, height, 0, width, height, length, bounds);
    addRectangle(&vertices, &uvs, 0, 0, 0, width, height, 0, width, height, length, bounds);

    setupNormals(&normals, vertices);

    model.loadVertices(vertices, uvs, normals, "imgs/stone.jpg");

    model.entity.position.x = worldX;
    model.entity.position.y = worldY;
    model.entity.position.z = worldZ;  // Yeah i fucked up
}
