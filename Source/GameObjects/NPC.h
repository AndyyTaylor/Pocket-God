#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include "../Entity.h"
#include "../Model.h"
#include "../Terrain/Terrain.h"

class NPC : public Entity {
public:
    NPC(float x, float y, float z);
    
    void update(float dt, std::vector<Terrain>* terrains);
    
    Model m_model;
private:
    glm::vec3 dpos;
    float speed = 50;
};

#endif