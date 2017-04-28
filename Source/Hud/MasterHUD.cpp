// Copyright 2017 Andy Taylor
#include "MasterHUD.h"

#include <iostream>
#include <string>

#include "../Shaders/Shader_Program.h"
#include "HUDComponent.h"
#include "Image.h"

MasterHUD::MasterHUD(std::string vertPath, std::string fragPath)
: shaderProgram(vertPath, fragPath) {
    Image component = Image(100, 0, 50, 50, "Coin.png");
    components.push_back(component);
}

void MasterHUD::render() {
    shaderProgram.bind();

    for (int i = 0; i < components.size(); i++) {
        components[i].draw();
    }

    shaderProgram.unbind();
}
