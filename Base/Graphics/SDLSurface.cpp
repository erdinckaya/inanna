//
// Created by misterdortnal on 21.11.2018.
//

#include "SDLSurface.h"



Inanna::SDLSurface::SDLSurface(const char *filename) : SDLSurface(IMG_Load(filename)) {
}

Inanna::SDLSurface::SDLSurface(SDL_Surface *surface)
        : surface(surface, (void (&&)(SDL_Surface *)) SDL_FreeSurface), textureId(new unsigned int, &DeleteTexture) {
    if (surface == nullptr) {
        throw std::runtime_error(std::string("Unable to load surface"));
    }
    glGenTextures(1, textureId.get());
    glBindTexture(GL_TEXTURE_2D, *textureId);
    GLenum mode;
    switch (surface->format->BytesPerPixel) {
        case 4:
            mode = GL_RGBA;
            break;
        case 3:
            mode = GL_RGB;
            break;
        case 1:
            mode = GL_LUMINANCE_ALPHA;
            break;
        default:
            throw std::runtime_error("Image with unknown channel profile");
    }
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Inanna::SDLSurface::DeleteTexture(unsigned int *textureId) {
    glDeleteTextures(1, textureId);
}

void Inanna::SDLSurface::Bind() {
    glBindTexture(GL_TEXTURE_2D, *textureId);
}

int Inanna::SDLSurface::Width() const {
    return surface->w;
}

int Inanna::SDLSurface::Height() const {
    return surface->h;
}

Inanna::SDLSurface::operator SDL_Surface *() {
    return surface.get();
}