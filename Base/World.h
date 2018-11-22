//
// Created by misterdortnal on 21.11.2018.
//

#ifndef INANNA_WORLD_H
#define INANNA_WORLD_H

#include "Graphics/Graphics.h"
#include "UI/WindowManager.h"

namespace Inanna {
    const unsigned int WIDTH = 900;
    const unsigned int HEIGHT = 900;
    const float FPS = 60;

    class World {

    public:
        World();
        ~World();

        void Start();

        void OnEvent(SDL_Event *event);

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
