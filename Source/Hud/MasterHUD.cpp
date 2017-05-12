// Copyright 2017 Andy Taylor
#include "MasterHUD.h"

#include <iostream>
#include <string>

#include "../Shaders/Shader_Program.h"
#include "HUDComponent.h"
#include "Image.h"
#include "Rect.h"
#include "Text.h"

MasterHUD::MasterHUD(std::string vertPath, std::string fragPath, std::string frag2Path)
: shaderProgram(vertPath, fragPath)
, sShader(vertPath, frag2Path) {
    Image component = Image(500, 5, 50, 50, "Coin.png");
    components.push_back(component);
    component = Image(0, 5, 50, 50, "menu.png");
    components.push_back(component);
    component = Image(800, 5, 50, 50, "Clock.png");
    components.push_back(component);

    // Text t = Text(100, 0, 300, 50, "main.png");
    // components.push_back(t);

    Rect c = Rect(0, 0, 1280, 60, glm::vec4(1.0, 1.0, 1.0, 1.0));
    components.push_back(c);
}

void MasterHUD::render() {
    sShader.bind();

    for (int i = 0; i < components.size(); i++) {
        if (components[i].type == 0) {
            // std::cout << components[i].getColour().x << std::endl;
            sShader.loadColour(components[i].getColour());
            components[i].draw();
        }
    }

    sShader.unbind();

    shaderProgram.bind();

    for (int i = 0; i < components.size(); i++) {
        if (components[i].type != 0) components[i].draw();  // HACK replace 0 with a global ENUM
    }

    shaderProgram.unbind();
}
