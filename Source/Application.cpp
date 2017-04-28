// Copyright 2017 Andy Taylor
#include "Application.h"

#include "Display.h"
#include "Glm_common.h"
#include "Math/Matrix.h"
#include "Entity.h"

#include <chrono>  // NOLINT - <chrono> is unnaproved

Application::Application()
: simpleShader("/Data/Shaders/vert.glsl", "/Data/Shaders/frag.glsl")
, hud("/Data/Shaders/2dvert.glsl", "/Data/Shaders/2dfrag.glsl") {
}

void Application::runMainGameLoop() {
    while (Display::isOpen()) {
        float delta = getDelta()/1000;

        Display::clear();
        simpleShader.bind();

        eventHandler.input(&camera, &player, &terrain);
        player.update(delta, &terrain);
        camera.update((Entity) player);

        glm::mat4 m = Maths::createModelMatrix(terrain.model.entity);
        glm::mat4 v = Maths::createViewMatrix(camera);
        glm::mat4 mvp = Maths::createProjMatrix() * v * m;
        simpleShader.loadMVP(mvp, m, v);

        terrain.model.draw();

        simpleShader.unbind();

        hud.render();

        Display::update();

        float fps = 1/delta;
        // std::cout << fps << std::endl;
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
