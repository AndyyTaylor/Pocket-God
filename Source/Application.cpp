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
#include <cstdlib>
#include <ctime>

extern std::string PROJECT_PATH;

Application::Application()
: simpleShader("/Data/Shaders/vert.glsl", "/Data/Shaders/frag.glsl") // At this point I shouldn't bother passing in shaders
, hud("/Data/Shaders/2dvert.glsl", "/Data/Shaders/2dfragtex.glsl", "/Data/Shaders/2dfragcol.glsl")
, interactHUD("/Data/Shaders/2dvert.glsl", "/Data/Shaders/2dfragtex.glsl", "/Data/Shaders/2dfragcol.glsl")
, menuHUD("/Data/Shaders/2dvert.glsl", "/Data/Shaders/2dfragtex.glsl", "/Data/Shaders/2dfragcol.glsl")
, endHUD("/Data/Shaders/2dvert.glsl", "/Data/Shaders/2dfragtex.glsl", "/Data/Shaders/2dfragcol.glsl") {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            Terrain t = Terrain(y*800, x*800);
            terrains.push_back(t);
        }
    }
    
    hud.components.push_back(Image(500, 5, 50, 50, "Coin.png"));
    hud.components.push_back(Image(1000, 5, 50, 50, "Clock.png"));
    hud.components.push_back(Text(550, 5, 50, 50, "$100", "bmpfont.png"));
    hud.components.push_back(Text(1050, 5, 50, 50, "10:00", "bmpfont.png"));
    hud.components.push_back(Text(20, 5, 50, 50, "Events", "bmpfont.png"));
    hud.components.push_back(Rect(0, 0, 1280, 60, glm::vec4(1.0, 1.0, 1.0, 1.0)));
    
    interactHUD.components.push_back(Text(100, 600, 60, 60, "Press E to trade", "bmpfont.png"));
    // interactHUD.components.push_back(Image(300, 300, 50, 50, "ekey.png"));
    menuHUD.components.push_back(Rect(200, 80, 900, 600, glm::vec4(0, 0, 1, 1.0)));
    menuHUD.components.push_back(Text(400, 100, 70, 70, "Title", "bmpfont.png"));
    menuHUD.components.push_back(Text(210, 180, 50, 50, "Name    Amt", "bmpfont.png"));
    for (int i = 0; i < 8; i++) {
        menuHUD.components.push_back(Text(210, 240+50*i, 40, 40, "Item " + std::to_string(i), "bmpfont.png"));
    }
    
    endHUD.components.push_back(Text(20, 5, 50, 50, "Score", "bmpfont.png"));
    endHUD.components.push_back(Image(100, 100, 500, 500, "Coin.png"));
    endHUD.components.push_back(Text(20, 600, 50, 50, "Press any key", "bmpfont.png"));
    endHUD.components.push_back(Text(20, 660, 50, 50, "to continue", "bmpfont.png"));
    
    NPC n = NPC(200, 0, 200, {1, 0.85, 1, 1, 1, 1.2, 1.1, 1.1}, "/Data/models/lumberJack.obj", "models/lumberJack_diffuse.png");
    npcs.push_back(n);
    
    n = NPC(2800, 0, 200, {1, 1.1, 0.95, 1, 0.85, 0.9, 1, 1}, "/Data/models/landlord.obj", "models/LandLord_diffuse.png");
    npcs.push_back(n);
    
    n = NPC(2800, 0, 2800, {1.1, 0.9, 1, 1, 1.05, 1, 1, 1.3}, "/Data/models/fox.obj", "");
    n.scale = glm::vec3(0.9, 0.9, 0.9);
    npcs.push_back(n);
    
    n = NPC(1400, 0, 1400, {1.2, 1, 1, 1.2, 1.05, 1, 1, 0.9}, "/Data/models/lumberJack.obj", "models/lumberJack_diffuse.png");
    npcs.push_back(n);
    
    n = NPC(200, 0, 2800, {1.1, 0.9, 1, 1, 1.05, 1, 0.85, 1.1}, "/Data/models/landlord.obj", "models/LandLord_diffuse.png");
    npcs.push_back(n);
    
    start = std::chrono::high_resolution_clock::now();
    srand((unsigned)time(0));
    getDelta();
}

void Application::runMainGameLoop() {
    while (Display::isOpen()) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> totaltime(currentTime-start);
        int timeinsec = (int) std::chrono::duration_cast<std::chrono::seconds>(totaltime).count();
        
        float delta = getDelta()/1000;
        

        Display::clear();
        simpleShader.bind();
        
        if (timeinsec > 180) {
            if (!player.gameEnded) {
                player.gameEnded = true;
                endHUD.updateText({"Score: " + std::to_string((int) player.coins)});
            } if (player.restartGame) {
                player.gameEnded = false;
                start = std::chrono::high_resolution_clock::now();
                player.coins = 50;
            }
            if (!Display::isOpen()) break;
            eventHandler.input(&player);
            
            endHUD.render();
            Display::update();
            continue;
        }
        
        interactHUD.visible = false;
        
        eventHandler.input(&player);
        if (!player.interacting) {
            player.update(delta, &terrains);
        }
        camera.update((Entity) player);
        
        for (int i = 0; i < npcs.size(); i++) {
            if (!player.interacting) npcs[i].update(delta, &terrains);
            
            npcs[i].interacting = false;
            // std::cout << player.position.x - npcs[i].position.x << ", " << player.position.z - npcs[i].position.z << std::endl;
            if (sqrt( (player.position.x - npcs[i].position.x)*(player.position.x - npcs[i].position.x) + (player.position.z - npcs[i].position.z)*(player.position.z - npcs[i].position.z) ) < 150) {
                interactHUD.visible = true;
                npcs[i].interacting = true;
            }
        }
        
        if (player.interacting) {
            bool buy = player.buying();
            bool sell = player.selling();
            if (!menuHUD.visible || player.changedSelection() || buy || sell) {
                std::vector<std::string> txt;
                if (!interactHUD.visible) {
                    txt = {"Inventory", "Name       Amount"};
                    for (int i = 0; i < itemnames.size(); i++) {
                        std::string s1 = std::to_string(i+1) + "." + itemnames[i];
                        while (s1.length() < 14) s1 += " ";
                        txt.push_back(s1 + std::to_string(player.itemsowned[i]));
                    }
                } else {
                    txt = {"NPC"};
                    if (player.selectedItem == -1) txt.push_back("Name       Price");
                    else txt.push_back("b(buy) / s(sell)");
                    NPC n = NPC();
                    for (int i = 0; i < npcs.size(); i++) if (npcs[i].interacting) n = npcs[i];
                    
                    for (int i = 0; i < itemnames.size(); i++) {
                        if (player.selectedItem == -1 || player.selectedItem == i) {
                            std::string s1 = std::to_string(i+1) + "." + itemnames[i];
                            while (s1.length() < 14) s1 += " ";
                            int price = (prices[i] * n.priceoffsets[i]);
                            if (i == eventItem) price *= eventMod;
                            txt.push_back(s1 + std::to_string(price));
                        } else {
                            txt.push_back("");
                        }
                    }
                    
                    if (player.selectedItem != -1 && (buy || sell)) {
                        int price = (prices[player.selectedItem] * n.priceoffsets[player.selectedItem]);
                        if (player.selectedItem == eventItem) price *= eventMod;
                        if (buy) {
                            if (player.coins >= price) {
                                player.coins -= price;
                                player.itemsowned[player.selectedItem] += 1;
                            }
                        } if (sell) {
                            if (player.itemsowned[player.selectedItem] > 0) {
                                player.coins += price*0.9;
                                player.itemsowned[player.selectedItem] -= 1;
                            }
                        }
                    }
                }
                
                menuHUD.updateText(txt);
                menuHUD.visible = true;
            }
        } else {
            menuHUD.visible = false;
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
        
        
        if (timeinsec % 10 == 0) {
            if (rand()%3==0){
                eventMod = rand()%6;
                eventItem = rand()%8;
            } else {
                eventItem = -1;
            }
        }
        
        if (player.coinsChanged() || prevtimeinsec != timeinsec || prevEventItem != eventItem || prevEventMod != eventMod) {
            std::string estring;
            if (eventItem != -1) {
                estring = itemnames[eventItem] + "x" + std::to_string(eventMod);
            } else {
                estring = "Events";
            }
            hud.updateText({std::to_string((int) player.coins), std::to_string(180-timeinsec), estring});
            prevtimeinsec = timeinsec;
            prevEventMod = eventMod;
            prevEventItem = eventItem;
        }
        
        
        hud.render();
        if (!player.interacting) interactHUD.render();
        menuHUD.render();

        Display::update();

        float fps = 1/delta;
        // std::cout << "FPS2: " << fps << std::endl;
    }
    
}

double Application::getDelta() {
    // I usually try not to use auto but the data type here is stupidly long
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> delta(currentTime-timePrev);

    timePrev = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(delta).count();
}
