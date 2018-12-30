//
// Created by misterdortnal on 21.11.2018.
//

#ifndef INANNA_WORLD_H
#define INANNA_WORLD_H

#include <SDL.h>

#include "Graphics/Graphics.h"
#include "UI/WindowManager.h"
#include "Input/KeyInput.h"
#include "Input/MouseInput.h"

namespace Inanna {
    const unsigned int SCREEN_WIDTH = 900;
    const unsigned int SCREEN_HEIGHT = 900;
    const float FPS = 60;

    class World {

    public:
        World();

        ~World();

        void Start();

        void OnEvent(SDL_Event *event);

        void OnMouseEvent(SDL_MouseButtonEvent event);

        void OnMouseMotionEvent(SDL_MouseMotionEvent event);

        void OnMouseWheelEvent(SDL_MouseWheelEvent event);

    private:
        bool isExist;

        std::unique_ptr<Graphics> graphics;
        std::unique_ptr<WindowManager> windowManager;


        void BringDoom();

        void OnTest(SDL_Keycode code);

        void OnRender(float dt);
    };
}

#endif //INANNA_WORLD_H
