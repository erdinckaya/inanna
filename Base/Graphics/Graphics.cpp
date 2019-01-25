//
// Created by misterdortnal on 21.11.2018.
//


#include "Graphics.h"
#include "../UI/WindowManager.h"
#include "../SpriteAnimation/Components/SpriteAnimation.h"
#include "../Game/Components/MoveCharacter.h"
#include "../Game/Command/Components/InputCommand.h"


Inanna::Graphics::Graphics(unsigned int width, unsigned int height, SDL_WindowFlags flags) : sdl(flags),
                                                                                             window(width, height),
                                                                                             context(window) {
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

    glClear(GL_COLOR_BUFFER_BIT);
    window.Show();
#ifdef MONITORX_DEBUG
    monitorX = std::make_unique<monitorx::MonitorX>(&WindowManager::spriteAnimationFactory, window, context.Get());
    monitorX->Init();
#endif
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

void Inanna::Graphics::DrawTexture(ImageAsset image, Rectf clip, Rectf destination, float angle, Vecf scale) {
    glEnable(GL_TEXTURE_2D);

    SDLSurface &surface = *spriteSheets[image.parent];
    surface.Bind();

    float final_w = destination.w * scale.x;
    float final_h = destination.h * scale.y;

    float final_x = destination.x - (final_w - destination.w) * 0.5f;
    float final_y = destination.y - (final_h - destination.h) * 0.5f;
    destination = Rectf(final_x, final_y, final_w, final_h);

    float part_x = (image.x + clip.x) / surface.Width();
    float part_w = part_x + (clip.w / surface.Width());
    float part_y = (image.y + clip.y) / surface.Height();
    float part_h = part_y + (clip.h / surface.Height());

    float center_x = destination.x + destination.w * 0.5f;
    float center_y = destination.y + destination.h * 0.5f;

    glPushMatrix();
    glTranslatef(center_x, center_y, 0);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(-center_x, -center_y, 0);

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
// draw model
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void Inanna::Graphics::Update(float dt) {
#ifdef MONITORX_DEBUG
    monitorX->Render<Renderable, Position, SpriteAnimation, MoveCharacter, InputCommand, end_of_list>();
#endif
    SDL_GL_MakeCurrent(window, context);
    SDL_GL_SwapWindow(window);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Inanna::Graphics::PassEvent(SDL_Event *event) {
#ifdef MONITORX_DEBUG
    monitorX->ProcessEvent(event);
#endif
}
