// Copyright 2017 Andy Taylor
#ifndef RECT_H_INCLUDED
#define RECT_H_INCLUDED

#include <GL/glew.h>
#include <vector>
#include <string>

#include "HUDComponent.h"
#include "../Glm_common.h"

class Rect : public HUDComponent{
 public:
    Rect(int x2, int y2, int w, int h, glm::vec4 color);

    void setupBuffers();

 protected:
    std::vector<glm::vec2> uvs;

    void generateVertices();
};

#endif  /* Image */
