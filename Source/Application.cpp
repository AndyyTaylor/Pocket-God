// Copyright 2017 Andy Taylor
#include "Application.h"

#include "Display.h"
#include "Glm_common.h"
#include "Math/Matrix.h"
#include "Entity.h"
#include "Hud/Image.h"
#include "Hud/Rect.h"
#include "Hud/Text.h"

#include <chrono>  // NOLINT - <chrono> is unnaproved
#include <string>

extern std::string PROJECT_PATH;

Application::Application()
: simpleShader("/Data/Shaders/vert.glsl", "/Data/Shaders/frag.glsl")
, hud("/Data/Shaders/2dvert.glsl", "/Data/Shaders/2dfragtex.glsl", "/Data/Shaders/2dfragcol.glsl")
, interactHUD("/Data/Shaders/2dvert.glsl", "/Data/Shaders/2dfragtex.glsl", "/Data/Shaders/2dfragcol.glsl") {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            Terrain t = Terrain(y*800, x*800);
            terrains.push_back(t);
        }
    }
    
    hud.components.push_back(Image(500, 5, 50, 50, "Coin.png"));
    hud.components.push_back(Image(0, 5, 50, 50, "menu.png"));
    hud.components.push_back(Image(800, 5, 50, 50, "Clock.png"));
    hud.components.push_back(Text(550, 5, 50, 50, "$100", "bmpfont.png"));
    hud.components.push_back(Text(850, 5, 50, 50, "10:00", "bmpfont.png"));
    hud.components.push_back(Rect(0, 0, 1280, 60, glm::vec4(1.0, 1.0, 1.0, 1.0)));
    
    interactHUD.components.push_back(Text(100, 300, 60, 60, "Press E to trade", "bmpfont.png"));
    // interactHUD.components.push_back(Image(300, 300, 50, 50, "ekey.png"));
    
    NPC n = NPC(200, 0, 200);
    npcs.push_back(n);
    
    getDelta();
}

void Application::runMainGameLoop() {
    while (Display::isOpen()) {
        float delta = getDelta()/1000;

        Display::clear();
        simpleShader.bind();
        interactHUD.visible = false;
        
        eventHandler.input(&camera, &player, &terrains);
        player.update(delta, &terrains);
        camera.update((Entity) player);
        for (int i = 0; i < npcs.size(); i++) {
            npcs[i].update(delta, &terrains);
            
            if (sqrt( (player.position.x - npcs[i].position.x)*(player.position.x - npcs[i].position.x) - (player.position.z - npcs[i].position.z)*(player.position.z - npcs[i].position.z) ) < 150) {
                interactHUD.visible = true;
            }
        }

        for (int i = 0; i < terrains.size(); i++) {
            glm::mat4 m = Maths::createModelMatrix(terrains[i].model.entity);
            glm::mat4 v = Maths::createViewMatrix(camera);
            glm::mat4 mvp = Maths::createProjMatrix() * v * m;
            simpleShader.loadMVP(mvp, m, v);

            terrains[i].model.draw();
        }
        
        for (int i = 0; i < npcs.size(); i++) {
            glm::mat4 m = Maths::createModelMatrix(npcs[i]);
            glm::mat4 v = Maths::createViewMatrix(camera);
            glm::mat4 mvp = Maths::createProjMatrix() * v * m;
            simpleShader.loadMVP(mvp, m, v);

            npcs[i].m_model.draw();
        }

        simpleShader.unbind();

        hud.render();
        interactHUD.render();

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
