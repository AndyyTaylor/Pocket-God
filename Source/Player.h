// Copyright 2017 Andy Taylor
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Entity.h"
#include "Terrain/Terrain.h"

class Player : public Entity {
 public:
    bool movingLeft = false, movingRight = false,
      movingUp = false, movingDown = false,
      movingForward = false, movingBackward = false;

    void update(float dt, Terrain* terrain);

 protected:
    float speed = 150, jumpheight = 250;
    bool isOnGround = false;

    glm::vec3 dpos;
};


#endif  /* PLAYER_H */
