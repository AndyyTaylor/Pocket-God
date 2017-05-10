// Copyright 2017 Andy Taylor
#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <GL/glew.h>
#include <vector>
#include <string>

#include "HUDComponent.h"
#include "../Glm_common.h"

class Image : public HUDComponent {
 public:
    Image(int x2, int y2, int w, int h, std::string filename);

    void setupBuffers();

 protected:
    std::vector<glm::vec2> uvs;
    std::string filename;

    void generateVertices();
};

#endif  /* Image */
