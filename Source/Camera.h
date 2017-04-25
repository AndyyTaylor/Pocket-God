// Copyright 2017 Andy Taylor
#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Entity.h"

class Camera : public Entity {
 public:
    Camera();

    void update(Entity entity);
};


#endif  /* CAMERA_H */
