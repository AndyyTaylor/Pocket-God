// Copyright 2017 Andy Taylor
#include "Player.h"

#include <iostream>
#include <vector>

#include "Terrain/Terrain.h"

void Player::update(float dt, std::vector<Terrain>* terrains) {
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

    if (movingUp && (true||isOnGround)) {
        dpos.y = jumpheight;
    }

    dpos.y -= 9.8;

    position += dpos*dt;

    int index = floor(position.x / 800.0f) + 4 * (floor(position.z / 800.0f));
    if (index < 0 || index >= terrains->size()) {
        // std::cout << "Index broken" << std::endl;
        index  = 0;
    }
    // std::cout << "Index: " << index << std::endl;
    Terrain t = (*terrains)[index];
    // float minHeight = t.getHeightAt((int) position.x % 800, (int) position.z % 800);
    float minHeight = -100;
    if (position.y < minHeight) {
        position.y = minHeight;
        isOnGround = true;
    } else {
        isOnGround = false;
    }

    // if (position.y < 0) position.y = 0;
}
