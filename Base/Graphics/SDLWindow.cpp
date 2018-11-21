//
// Created by misterdortnal on 21.11.2018.
//

#include "SDLWindow.h"


Inanna::SDLWindow::SDLWindow(unsigned int width, unsigned int height)
        : window(SDL_CreateWindow("Inanna", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                                  SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL), (void (&&)(SDL_Window *)) SDL_DestroyWindow) {
    if (window == nullptr) {
        throw std::runtime_error(std::string("Error creating window: ") + SDL_GetError());
    }
}


Inanna::SDLWindow::operator SDL_Window *() {
    return window.get();
}

void Inanna::SDLWindow::Show() {
    SDL_ShowWindow(window.get());
}
