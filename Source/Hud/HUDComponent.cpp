// Copyright 2017 Andy Taylor
#include "HUDComponent.h"

#include <GL/glew.h>
#include <iostream>

void HUDComponent::draw() {
    bind();

    // std::cout << vertices.size() << std::endl;
    if (type > 0) glBindTexture(GL_TEXTURE_2D, TextureID);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    unbind();
}
