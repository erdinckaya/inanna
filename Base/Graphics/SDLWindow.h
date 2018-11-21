//
// Created by misterdortnal on 21.11.2018.
//

#ifndef INANNA_SDL_WINDO_H
#define INANNA_SDL_WINDO_H


#include <memory>
#include <SDL.h>

struct SDL_Window;

namespace Inanna {
    class SDLWindow {
    public:
        SDLWindow(unsigned int width, unsigned int height);

        operator SDL_Window *();

        void Show();

    private:
        std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> window;
    };
}


#endif //INANNA_SDL_WINDO_H
