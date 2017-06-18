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
    
}

void MasterHUD::render() {
    if (!visible) return;
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

void MasterHUD::updateText(std::vector<std::string> txt) {
    int index = 0;
    for (int i = 0; i < components.size(); i++) {
        if (components[i].type == 1) {
            components[i].loadText(txt[index], "bmpfont.png");
            index++;
            if (index >= txt.size()) return;
        }
    }
}