//
// Created by misterdortnal on 21.11.2018.
//

#ifndef INANNA_WINDOWMANAGER_H
#define INANNA_WINDOWMANAGER_H

#define WINDOW_MANAGER_TEST

#include <entityx/entityx.h>
#include "../Graphics/Graphics.h"


namespace Inanna {
    class WindowManager : public entityx::EntityX {
    public:
        explicit WindowManager(float width, float height, Graphics* graphics);

        void Update(entityx::TimeDelta dt);

        void Test(SDL_Keycode code);
        void TestMouseButton(SDL_MouseButtonEvent event);
        void TestMouseMotion(SDL_MouseMotionEvent event);
        void TestMouseWheel(SDL_MouseWheelEvent event);
    private:
        float width;
        float height;

        Graphics* graphics;

#ifdef WINDOW_MANAGER_TEST
        entityx::Entity parent;
        entityx::Entity child;
#endif
    };
}




#endif //INANNA_WINDOWMANAGER_H
