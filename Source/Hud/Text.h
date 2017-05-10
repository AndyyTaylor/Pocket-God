// Copyright 2017 Andy Taylor
#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <GL/glew.h>
#include <vector>
#include <string>

#include "HUDComponent.h"
#include "../Glm_common.h"

class Text : public HUDComponent{
 public:
    Text(int x2, int y2, int w, int h, std::string filename);

    void setupBuffers();

 protected:
    std::vector<glm::vec2> uvs;
    std::string filename;

    void generateVertices();
};

#endif  /* Image */
