// Copyright 2017 Andy Taylor
#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Shaders/Shader_Program.h"
#include "EventHandler.h"
#include "Model.h"
#include "Terrain/Terrain.h"
#include "Camera.h"
#include "Player.h"

#include <chrono>  // NOLINT - <chrono> is unapproved

class Application {
 public:
    Application();

    void input();
    void runMainGameLoop();

    double getDelta();

 private:
    Shader::Shader_Program shaderProgram;
    Model model;
    EventHandler eventHandler;
    Terrain terrain;
    Camera camera;
    Player player;

    std::chrono::high_resolution_clock::time_point timePrev;
};

#endif /* APPLICATION_H_ */
