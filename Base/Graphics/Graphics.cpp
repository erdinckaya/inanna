//
// Created by misterdortnal on 21.11.2018.
//


#include "Graphics.h"


Inanna::Graphics::Graphics(unsigned int width, unsigned int height, SDL_WindowFlags flags) : sdl(flags),
                                                                                             window(width, height),
                                                                                             context(window) {

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetSwapInterval(1);

    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    InitResources();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    window.Show();
}


Inanna::Graphics::~Graphics() = default;


void Inanna::Graphics::InitResources() {
    auto sheetCount = Resources::SheetCount;
    auto sheets = Resources::Sheets;
    for (int i = 0; i < sheetCount; ++i) {
        auto sheet = sheets[i];
        spriteSheets.insert({sheet.name, std::make_unique<SDLSurface>(sheet.path)});
    }
}

void Inanna::Graphics::DrawTexture(ImageAsset image, Rectf clip, Rectf destination) {
    glEnable(GL_TEXTURE_2D);

    SDLSurface &surface = *spriteSheets[image.parent];
    surface.Bind();

    float part_x = (image.x + clip.x) / surface.Width();
    float part_w = part_x + (clip.w / surface.Width());
    float part_y = (image.y + clip.y) / surface.Height();
    float part_h = part_y + (clip.h / surface.Height());

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(part_x, part_h);
    glVertex2f(destination.x, destination.y + destination.h);
    glTexCoord2f(part_w, part_h);
    glVertex2f(destination.x + destination.w, destination.y + destination.h);
    glTexCoord2f(part_w, part_y);
    glVertex2f(destination.x + destination.w, destination.y);
    glTexCoord2f(part_x, part_y);
    glVertex2f(destination.x, destination.y);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Inanna::Graphics::Update(float dt) {
    SDL_GL_SwapWindow(window);
    glClear(GL_COLOR_BUFFER_BIT);
}
