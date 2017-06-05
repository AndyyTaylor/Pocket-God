#include "NPC.h"
#include <iostream>
#include "../Terrain/Terrain.h"

extern std::string PROJECT_PATH;

NPC::NPC(float x, float y, float z) {
    position = glm::vec3(x, y, z);
    scale = glm::vec3(45, 45, 45);
    m_model.loadModel((PROJECT_PATH + "/Data/models/lumberJack.obj").c_str());
    m_model.setupBuffers("models/lumberJack_diffuse.png");
}

void NPC::update(float dt, std::vector<Terrain>* terrains) {
    dpos.x = 0;
    dpos.z = 0;
    
    dpos.x += cos(glm::radians(-rotation.y + 90)) * speed;
    dpos.z += sin(glm::radians(-rotation.y + 90)) * speed;
    
    rotation.y += 20*dt;
    
    dpos.y -= 9.8;
    
    position += dpos*dt;
    
    int index = floor(position.x / 800.0f) + 4 * (floor(position.z / 800.0f));
    if (index < 0 || index >= terrains->size()) {
        // std::cout << "Index broken" << std::endl;
        index  = 0;
    }
    // std::cout << "Index: " << index << std::endl;
    Terrain t = (*terrains)[index];
    float minHeight = t.getHeightAt((int) position.x % 800, (int) position.z % 800);
    if (position.y < minHeight + scale.y) {
        position.y = minHeight + scale.y;
        dpos.y = 0;
    }
}