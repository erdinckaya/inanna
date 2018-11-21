//
// Created by misterdortnal on 21.11.2018.
//

#include <GLES2/gl2.h>
#include <GL/gl.h>
#include "Graphics.h"


Inanna::Graphics::Graphics(unsigned int width, unsigned int height, SDL_WindowFlags flags) : sdl(flags), window(width, height),
                                                                                     context(window) {

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetSwapInterval(1);

    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    initResources();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    window.Show();
}


Inanna::Graphics::~Graphics() = default;


void Inanna::Graphics::initResources() {

}

void Inanna::Graphics::Update(float dt) {
    SDL_GL_SwapWindow(window);
    glClear(GL_COLOR_BUFFER_BIT);
}
