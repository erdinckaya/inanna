//
// Created by misterdortnal on 21.11.2018.
//


#define GRAPHICS_TEST

#include <SDL.h>
#include "World.h"
#include "Graphics/Graphics.h"
#include "UI/WindowManager.h"

Inanna::World::World() : isExist(true) {
    graphics = std::make_unique<Graphics>(WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    windowManager = std::make_unique<WindowManager>(WIDTH, HEIGHT, graphics.get());
}

Inanna::World::~World() {
    BringDoom();
}


void Inanna::World::Start() {

    SDL_Event event{};
    while (isExist) {

        const Uint32 start_time_ms = SDL_GetTicks();
//        input.beginNewFrame();
        while (SDL_PollEvent(&event)) {
            OnEvent(&event);
        }

//        OnLoop();

        windowManager->Update(1000/*ms*/ / FPS);
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


void Inanna::World::OnEvent(SDL_Event *event) {
//    EventManager::OnEvent(event);
    switch (event->type) {
        case SDL_FINGERDOWN:
        case SDL_MOUSEBUTTONDOWN: {
//            for (int i = 0; i < 100; ++i) {
//                rigidBodies.push_back(new RigidBody(physics->CreateRectBody(event->button.x, event->button.y, 20, 20, true)));
//            }
//            windowManager->OnMouseButtonDownEvent(event->button);
            break;
        }
        case SDL_FINGERUP:
        case SDL_MOUSEBUTTONUP: {
//            rigidBodies.push_back(new RigidBody(physics->CreateRectBody(event->button.x, event->button.y, 20, 20, true)));
//            windowManager->OnMouseButtonUpEvent(event->button);
            break;
        }
        case SDL_FINGERMOTION:
        case SDL_MOUSEMOTION: {
//            windowManager->OnMouseMotionEvent(event->motion);
            break;
        }
        case SDL_MOUSEWHEEL: {
//            windowManager->OnMouseWheelEvent(event->wheel);
            break;
        }
        case SDL_KEYDOWN: {
#ifdef GRAPHICS_TEST
            OnTest(event->key.keysym.sym);
#endif
            break;
        }
        case SDL_QUIT: {
            BringDoom();
            break;
        }
        default:
            break;
    }
}

void Inanna::World::BringDoom() {
    isExist = false;

    SDL_Quit();
}

void Inanna::World::OnTest(SDL_Keycode code) {
    windowManager->Test(code);
}

void Inanna::World::OnRender(float dt) {
    graphics->Update(dt);
}
