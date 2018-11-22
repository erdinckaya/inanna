//
// Created by misterdortnal on 21.11.2018.
//

#ifndef INANNA_SURFACE_H
#define INANNA_SURFACE_H

#include <SDL_surface.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <memory>
#include <iostream>

namespace Inanna {
    class SDLSurface {
    public:
        SDLSurface(const char *filename);

        SDLSurface(SDL_Surface *surface);

        operator SDL_Surface *();

        void Bind();

        int Width() const;

        int Height() const;

    private:
        static void DeleteTexture(unsigned int *textureId);

        std::unique_ptr<SDL_Surface, void (*)(SDL_Surface *)> surface;
        std::unique_ptr<unsigned int, void (*)(unsigned int *)> textureId;
    };
}


#endif //INANNA_SURFACE_H
