#include "Camera.h"

#include <GL/glew.h>

Camera::Camera()
{
    position = glm::vec3(0, 1, -1);
}

void Camera::update(float dt)
{
    glm::vec3 change;

    if (movingForward){
        change.x -= cos(glm::radians(rotation.y + 90)) * speed;
        change.z -= sin(glm::radians(rotation.y + 90)) * speed;
    }
    if (movingBackward){
        change.x += cos(glm::radians(rotation.y + 90)) * speed;
        change.z += sin(glm::radians(rotation.y + 90)) * speed;
    }
    if (movingLeft){
        change.x -= cos(glm::radians(rotation.y)) * speed;
        change.z -= sin(glm::radians(rotation.y)) * speed;
    }
    if (movingRight){
        change.x += cos(glm::radians(rotation.y)) * speed;
        change.z += sin(glm::radians(rotation.y)) * speed;
    }
    if (movingUp){
        change.z += 2;
    }
    if (movingDown){
        change.z -= 2;
    }

    position += change*dt;
}
