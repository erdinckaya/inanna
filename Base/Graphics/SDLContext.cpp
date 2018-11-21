//
// Created by misterdortnal on 21.11.2018.
//

#include "SDLContext.h"

Inanna::SDLContext::SDLContext(SDLWindow &sdlWindow)
        : context(SDL_GL_CreateContext(sdlWindow), (void (&&)(SDL_GLContext)) SDL_GL_DeleteContext) {
    const char *error = SDL_GetError();
    if (*error != '\0') {
        throw std::runtime_error(std::string("Error initialising OpenGL context: ") + error);
    }
}

Inanna::SDLContext::operator SDL_GLContext() const {
    return context.get();
}