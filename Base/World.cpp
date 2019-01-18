//
// Created by misterdortnal on 21.11.2018.
//


#define GRAPHICS_TEST

#include "World.h"


Inanna::World::World() : isExist(true) {
    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 Core + GLSL 150
    const char *glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);


    graphics = std::make_unique<Graphics>(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GL_SetSwapInterval(1);
    windowManager = std::make_unique<WindowManager>(SCREEN_WIDTH, SCREEN_HEIGHT, graphics.get());
}

Inanna::World::~World() {
    BringDoom();
}


void Inanna::World::Start() {

    SDL_Event event{};
    while (isExist) {

        const Uint32 start_time_ms = SDL_GetTicks();
        KeyInput::Instance.BeginNewFrame();
        MouseInput::Instance.BeginNewFrame();
        while (SDL_PollEvent(&event)) {
            graphics->PassEvent(&event);
            OnEvent(&event);
        }

//        OnLoop();

        windowManager->
        Update(1000/*ms*/ / FPS);
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
    switch (event->type) {
        case SDL_FINGERDOWN:
        case SDL_MOUSEBUTTONDOWN: {
            MouseInput::Instance.MouseDownEvent(*event);
            OnMouseEvent(event->button);
            break;
        }
        case SDL_FINGERUP:
        case SDL_MOUSEBUTTONUP: {
            MouseInput::Instance.MouseUpEvent(*event);
            OnMouseEvent(event->button);
            break;
        }
        case SDL_FINGERMOTION:
        case SDL_MOUSEMOTION: {
            OnMouseMotionEvent(event->motion);
            break;
        }
        case SDL_MOUSEWHEEL: {
            OnMouseWheelEvent(event->wheel);
            break;
        }
        case SDL_KEYDOWN: {
            KeyInput::Instance.KeyDownEvent(*event);
#ifdef GRAPHICS_TEST
            OnTest(event->key.keysym.sym);
#endif
            break;
        }
        case SDL_KEYUP: {
            KeyInput::Instance.KeyUpEvent(*event);
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

void Inanna::World::OnMouseEvent(SDL_MouseButtonEvent event) {
    windowManager->TestMouseButton(event);
}

void Inanna::World::OnMouseMotionEvent(SDL_MouseMotionEvent event) {
    windowManager->TestMouseMotion(event);
}

void Inanna::World::OnMouseWheelEvent(SDL_MouseWheelEvent event) {
    windowManager->TestMouseWheel(event);
}
