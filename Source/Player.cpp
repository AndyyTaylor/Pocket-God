// Copyright 2017 Andy Taylor
#include "Player.h"

void Player::update(float dt) {
    glm::vec3 change;

    if (movingForward) {
        change.x -= cos(glm::radians(rotation.y + 90)) * speed;
        change.z -= sin(glm::radians(rotation.y + 90)) * speed;
    }
    if (movingBackward) {
        change.x += cos(glm::radians(rotation.y + 90)) * speed;
        change.z += sin(glm::radians(rotation.y + 90)) * speed;
    }
    if (movingLeft) {
        change.x -= cos(glm::radians(rotation.y)) * speed;
        change.z -= sin(glm::radians(rotation.y)) * speed;
    }
    if (movingRight) {
        change.x += cos(glm::radians(rotation.y)) * speed;
        change.z += sin(glm::radians(rotation.y)) * speed;
    }

    if (movingUp) {
        change.y += speed;
    }

    if (movingDown) {
        change.y -= speed;
    }

    //change.y -= 9.8;

    position += change*dt;

    //if (position.y < 0) position.y = 0;
}
