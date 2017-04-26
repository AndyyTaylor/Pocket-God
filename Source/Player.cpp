// Copyright 2017 Andy Taylor
#include "Player.h"

#include "Terrain/Terrain.h"

void Player::update(float dt, Terrain* terrain) {
    dpos.x = 0;
    dpos.z = 0;

    if (movingForward) {
        dpos.x -= cos(glm::radians(rotation.y + 90)) * speed;
        dpos.z -= sin(glm::radians(rotation.y + 90)) * speed;
    }
    if (movingBackward) {
        dpos.x += cos(glm::radians(rotation.y + 90)) * speed;
        dpos.z += sin(glm::radians(rotation.y + 90)) * speed;
    }
    if (movingLeft) {
        dpos.x -= cos(glm::radians(rotation.y)) * speed;
        dpos.z -= sin(glm::radians(rotation.y)) * speed;
    }
    if (movingRight) {
        dpos.x += cos(glm::radians(rotation.y)) * speed;
        dpos.z += sin(glm::radians(rotation.y)) * speed;
    }

    if (movingUp && isOnGround) {
        dpos.y = jumpheight;
    }

    dpos.y -= 9.8;

    position += dpos*dt;

    float minHeight = terrain->getHeightAt(position.x, position.z);
    if (position.y < minHeight) {
        position.y = minHeight;
        isOnGround = true;
    } else {
        isOnGround = false;
    }

    //if (position.y < 0) position.y = 0;
}
