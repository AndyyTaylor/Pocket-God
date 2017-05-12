// Copyright 2017 Andy Taylor
#ifndef APPLICATION_H_
#define APPLICATION_H_


#include <vector>
#include "Shaders/Shader_Program.h"
#include "EventHandler.h"
#include "Model.h"
#include "Terrain/MasterTerrain.h"
#include "Camera.h"
#include "Player.h"
#include "Hud/MasterHUD.h"

#include <chrono>  // NOLINT - <chrono> is unapproved

class Application {
 public:
    Application();

    void input();
    void runMainGameLoop();

    double getDelta();

 private:
    Shader::Shader_Program simpleShader;
    MasterHUD hud;
    Model model;
    EventHandler eventHandler;
    MasterTerrain terrain;
    Camera camera;
    Player player;

    std::chrono::high_resolution_clock::time_point timePrev;
};

#endif /* APPLICATION_H_ */
