//
// Created by misterdortnal on 21.11.2018.
//


#include "SDL.h"

Inanna::SDL::SDL(int flags) {
    if (SDL_Init(flags) != 0) {
        throw std::runtime_error("Failed to init SDL");
    }

    if (TTF_Init() == -1) {
        throw std::runtime_error("SDL_ttf could not initialize!");
    }
}

Inanna::SDL::~SDL() {
    TTF_Quit();
    SDL_Quit();
}