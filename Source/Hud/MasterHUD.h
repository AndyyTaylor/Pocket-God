// Copyright 2017 Andy Taylor
#ifndef MASTER_HUD_INCLUDED
#define MASTER_HUD_INCLUDED

#include <string>
#include <vector>

#include "../Shaders/Shader_Program.h"
#include "HUDComponent.h"

class MasterHUD {
 public:
    MasterHUD(std::string vertPath, std::string fragPath, std::string frag2Path);

    void render();
    void draw();
    void updateText(std::vector<std::string> text);
    
    std::vector<HUDComponent> components;
    bool visible = true;

 private:
    Shader::Shader_Program shaderProgram;
    Shader::Shader_Program sShader;
};

#endif  /* MasterHUD */
