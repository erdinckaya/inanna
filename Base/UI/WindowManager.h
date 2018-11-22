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

        float width;
        float height;
    private:
        Graphics* graphics;
    };
}




#endif //INANNA_WINDOWMANAGER_H
