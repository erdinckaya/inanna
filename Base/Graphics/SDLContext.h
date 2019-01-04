//
// Created by misterdortnal on 21.11.2018.
//

#ifndef INANNA_SDLCONTEXT_H
#define INANNA_SDLCONTEXT_H


#include <SDL_video.h>
#include <memory>
#include "SDLWindow.h"

class SDLWindow;

namespace Inanna {
    class SDLContext {
    public:
        SDLContext(SDLWindow &sdlWindow);

        operator SDL_GLContext() const;

#ifdef MONITORX_DEBUG
        SDL_GLContext* Get();
#endif

    private:
        std::unique_ptr<void, void (*)(SDL_GLContext)> context;
    };
}

#endif //INANNA_SDLCONTEXT_H
