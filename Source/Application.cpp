// Copyright 2017 Andy Taylor
#include "Application.h"

#include "Display.h"
#include "Glm_common.h"
#include "Math/Matrix.h"
#include "Entity.h"

#include <chrono>  // NOLINT - <chrono> is unnaproved
#include <string>

extern std::string PROJECT_PATH;

Application::Application()
: simpleShader("/Data/Shaders/vert.glsl", "/Data/Shaders/frag.glsl")
, hud("/Data/Shaders/2dvert.glsl", "/Data/Shaders/2dfragtex.glsl", "/Data/Shaders/2dfragcol.glsl") {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            Terrain t = Terrain(y*800, x*800);
            terrains.push_back(t);
        }
    }
}

void Application::runMainGameLoop() {
    while (Display::isOpen()) {
        float delta = getDelta()/1000;

        Display::clear();
        simpleShader.bind();

        eventHandler.input(&camera, &player, &terrains);
        player.update(delta, &terrains);
        camera.update((Entity) player);


        for (int i = 0; i < terrains.size(); i++) {
            glm::mat4 m = Maths::createModelMatrix(terrains[i].model.entity);
            glm::mat4 v = Maths::createViewMatrix(camera);
            glm::mat4 mvp = Maths::createProjMatrix() * v * m;
            simpleShader.loadMVP(mvp, m, v);

            terrains[i].model.draw();
        }

        simpleShader.unbind();

        hud.render();

        Display::update();

        float fps = 1/delta;
        // std::cout << "FPS2: " << fps << std::endl;
    }
    Display::close();
}

double Application::getDelta() {
    // I usually try not to use auto but the data type here is stupidly long
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> delta(currentTime-timePrev);

    timePrev = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(delta).count();
}
