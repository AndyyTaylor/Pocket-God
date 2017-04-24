#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Entity.h"

class Camera : public Entity
{
public:
    bool movingLeft = false, movingRight = false,
         movingUp = false, movingDown = false,
         movingForward = false, movingBackward = false;
    float speed = 5;

    Camera();

    void update(float delta);
};


#endif
