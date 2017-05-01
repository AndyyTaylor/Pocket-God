// Copyright 2017 Andy Taylor
#include "MasterHUD.h"

#include <iostream>
#include <string>

#include "../Shaders/Shader_Program.h"
#include "HUDComponent.h"
#include "Image.h"
#include "Rect.h"

MasterHUD::MasterHUD(std::string vertPath, std::string fragPath, std::string frag2Path)
: shaderProgram(vertPath, fragPath)
, simpleShader(vertPath, frag2Path) {
    Image component = Image(100, 0, 50, 50, "Coin.png");
    components.push_back(component);
    component = Image(0, 0, 50, 50, "menu.png");
    components.push_back(component);
    component = Image(200, 0, 50, 50, "Clock.png");
    components.push_back(component);

    Rect c = Rect(0, 0, 500, 100, glm::vec4(1.0, 1.0, 1.0, 1.0));
    components.push_back(c);
}

void MasterHUD::render() {
    shaderProgram.bind();

    for (int i = 0; i < components.size(); i++) {
        if (components[i].type != 0) components[i].draw();  // HACK replace 0 with a global ENUM
    }

    shaderProgram.unbind();

    simpleShader.bind();

    for (int i = 0; i < components.size(); i++) {
        if (components[i].type == 0) {
            // std::cout << components[i].getColour().x << std::endl;
            simpleShader.loadColour(components[i].getColour());
            components[i].draw();
        }
    }

    simpleShader.unbind();
}
