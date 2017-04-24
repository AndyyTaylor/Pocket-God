// Copyright 2017 Andy Taylor
#include "EventHandler.h"

#include <iostream>
#include <SDL2/SDL.h>
#include "Display.h"
#include "Camera.h"

EventHandler::EventHandler() {
}

void EventHandler::input(Camera* camera) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT
            || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
            Display::close();
        } else if (event.type == SDL_KEYDOWN) {
            SDL_Keycode key = event.key.keysym.sym;
            if (key == SDLK_w) {
                camera->movingForward = true;
            } else if (key == SDLK_s) {
                camera->movingBackward = true;
            } else if (key == SDLK_a) {
                camera->movingLeft = true;
            } else if (key == SDLK_d) {
                camera->movingRight = true;
            } else if (key == SDLK_SPACE) {
                camera->movingUp = true;
            } else if (key == SDLK_LSHIFT) {
                camera->movingDown = true;
            }
        } else if (event.type == SDL_KEYUP) {
            SDL_Keycode key = event.key.keysym.sym;
            if (key == SDLK_w) {
                camera->movingForward = false;
            } else if (key == SDLK_s) {
                camera->movingBackward = false;
            } else if (key == SDLK_a) {
                camera->movingLeft = false;
            } else if (key == SDLK_d) {
                camera->movingRight = false;
            } else if (key == SDLK_SPACE) {
                camera->movingUp = false;
            } else if (key == SDLK_LSHIFT) {
                camera->movingDown = false;
            }
        } else if (event.type == SDL_MOUSEMOTION) {
            camera->rotation.y -= event.motion.xrel/3;  // MOUSE_SENSITIVITY
            camera->rotation.x += event.motion.yrel/3;
        }
    }
}
