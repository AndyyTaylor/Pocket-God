#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include "../Entity.h"
#include "../Model.h"
#include "../Terrain/Terrain.h"

class NPC : public Entity {
public:
    NPC();
    NPC(float x, float y, float z, std::vector<float> priceoffsets);
    
    void update(float dt, std::vector<Terrain>* terrains);
    
    Model m_model;
    std::vector<float> priceoffsets;
    bool interacting = false;
    
private:
    glm::vec3 dpos;
    float speed = 50;
};

#endif