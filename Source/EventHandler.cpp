// Copyright 2017 Andy Taylor
#include "EventHandler.h"

#include <SDL2/SDL.h>

#include <iostream>
#include <vector>

#include "Display.h"
#include "Camera.h"
#include "GameObjects/Player.h"
#include "Terrain/Terrain.h"

EventHandler::EventHandler() {
}

void EventHandler::input(Player* player) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT
            || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
            Display::close();
        } else if (event.type == SDL_KEYDOWN) {
            SDL_Keycode key = event.key.keysym.sym;
            if (player->gameEnded) {
                player->restartGame = true;
            }
            if (key == SDLK_w) {
                player->movingForward = true;
            } else if (key == SDLK_s && !player->interacting) {
                player->movingBackward = true;
            } else if (key == SDLK_a) {
                player->movingLeft = true;
            } else if (key == SDLK_d) {
                player->movingRight = true;
            } else if (key == SDLK_SPACE) {
                player->movingUp = true;
            } else if (key == SDLK_LSHIFT) {
                player->movingDown = true;
            } else if (key == SDLK_r) {
                Display::toggleMesh();
            } else if (key == SDLK_e) {
                player->selectedItem = -1;
                if (player->interacting) {
                    player->interacting = false;
                } else {
                    player->interacting = true;
                }
            }
            else if (key == SDLK_0) player->selectedItem = -1;
            else if (key == SDLK_1) player->selectedItem = 0;
            else if (key == SDLK_2) player->selectedItem = 1;
            else if (key == SDLK_3) player->selectedItem = 2;
            else if (key == SDLK_4) player->selectedItem = 3;
            else if (key == SDLK_5) player->selectedItem = 4;
            else if (key == SDLK_6) player->selectedItem = 5;
            else if (key == SDLK_7) player->selectedItem = 6;
            else if (key == SDLK_8) player->selectedItem = 7;
            else if (key == SDLK_9) player->selectedItem = 8;
            else if (key == SDLK_b) player->buy = true;
            else if (key == SDLK_s) player->sell = true;
        } else if (event.type == SDL_KEYUP) {
            SDL_Keycode key = event.key.keysym.sym;
            if (key == SDLK_w) {
                player->movingForward = false;
            } else if (key == SDLK_s) {
                player->movingBackward = false;
            } else if (key == SDLK_a) {
                player->movingLeft = false;
            } else if (key == SDLK_d) {
                player->movingRight = false;
            } else if (key == SDLK_SPACE) {
                player->movingUp = false;
            } else if (key == SDLK_LSHIFT) {
                player->movingDown = false;
            }
        } else if (event.type == SDL_MOUSEMOTION) {
            player->rotation.y += event.motion.xrel/3;  // MOUSE_SENSITIVITY
            player->rotation.x += event.motion.yrel/3;
        } else if (event.type == SDL_MOUSEWHEEL) {
            //for (int i = 0; i < terrains->size(); i++) {
                /// Terrain* t = terrains[i];
                // t->updateDiv(event.wheel.y);
            //}
        }
    }
}
