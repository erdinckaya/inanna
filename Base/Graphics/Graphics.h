//
// Created by misterdortnal on 21.11.2018.
//

#ifndef INANNA_GRAPHICS_H
#define INANNA_GRAPHICS_H

#include "SDLWindow.h"
#include "SDLContext.h"
#include "SDL.h"

namespace Inanna {
    class Graphics {
    public:
        Graphics(unsigned int width, unsigned int height, SDL_WindowFlags flags);

        ~Graphics();

        void Update(float dt);
    private:
        SDL sdl;
        SDLWindow window;
        SDLContext context;

        void initResources();
    };
}


#endif //INANNA_GRAPHICS_H
