// Copyright 2017 Andy Taylor
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Entity.h"

class Player : public Entity {
 public:
    bool movingLeft = false, movingRight = false,
      movingUp = false, movingDown = false,
      movingForward = false, movingBackward = false;
    float speed = 50;

    void update(float dt);
};


#endif  /* PLAYER_H */
