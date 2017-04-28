// Copyright 2017 Andy Taylor
#ifndef MASTER_HUD_INCLUDED
#define MASTER_HUD_INCLUDED

#include <string>
#include <vector>

#include "../Shaders/Shader_Program.h"
#include "HUDComponent.h"

class MasterHUD {
 public:
    MasterHUD(std::string vertPath, std::string fragPath);

    void render();
    void draw();

 private:
    Shader::Shader_Program shaderProgram;
    std::vector<HUDComponent> components;
};

#endif  /* MasterHUD */
