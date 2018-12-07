//
// Created by misterdortnal on 21.11.2018.
//

#ifndef INANNA_WINDOWMANAGER_H
#define INANNA_WINDOWMANAGER_H

#define WINDOW_MANAGER_TEST

#include <entityx/entityx.h>
#include "../Graphics/Graphics.h"
#include "UIFactory.h"


namespace Inanna {
    class WindowManager {
    public:
        explicit WindowManager(float width, float height, Graphics *graphics);

        void Update(entityx::TimeDelta dt);

        void Test(SDL_Keycode code);

        void TestMouseButton(SDL_MouseButtonEvent event);

        void TestMouseMotion(SDL_MouseMotionEvent event);

        void TestMouseWheel(SDL_MouseWheelEvent event);


        static UIFactory uiFactory;
    private:
        float width;
        float height;

        Graphics *graphics;
    };
}


#endif //INANNA_WINDOWMANAGER_H
