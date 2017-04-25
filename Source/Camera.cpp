// Copyright 2017 Andy Taylor
#include "Camera.h"

#include <GL/glew.h>
#include "Entity.h"

Camera::Camera() {
    position = glm::vec3(0, 1, -1);
}

void Camera::update(Entity entity) {
    position = glm::vec3(entity.position.x, entity.position.y += 20, entity.position.z);
    rotation = entity.rotation;
}
