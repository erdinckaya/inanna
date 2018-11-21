//
// Created by misterdortnal on 21.11.2018.
//


#define GRAPHICS_TEST

#include <SDL.h>
#include "World.h"
#include "Graphics/Graphics.h"
#include "UI/WindowManager.h"

Inanna::World::World() : isExist(true) {
    graphics = std::make_unique<Graphics>((unsigned int) WIDTH, (unsigned int) HEIGHT, SDL_WINDOW_OPENGL);
}

Inanna::World::~World() {
    BringDoom();
}


void Inanna::World::Start() {

#ifdef GRAPHICS_TEST
    OnTest();
#endif

    SDL_Event event{};
    while (isExist) {

        const Uint32 start_time_ms = SDL_GetTicks();
//        input.beginNewFrame();
//        while (SDL_PollEvent(&event)) {
//            OnEvent(&event);
//        }

//        OnLoop();
        OnRender(FPS);
//        physics->Update(kFps);
        const auto ms_per_frame = static_cast<const Uint32>(1000/*ms*/ / FPS);
        const Uint32 elapsed_time_ms = SDL_GetTicks() - start_time_ms;
        if (elapsed_time_ms < ms_per_frame) {
            SDL_Delay(ms_per_frame - elapsed_time_ms);
        }

//        CleanMarkedObjects();
    }

    BringDoom();
}

void Inanna::World::BringDoom() {
    SDL_Quit();
}

void Inanna::World::OnTest() {

}

void Inanna::World::OnRender(float dt) {
    graphics->Update(dt);
}
