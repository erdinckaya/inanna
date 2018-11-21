//
// Created by misterdortnal on 21.11.2018.
//

#ifndef INANNA_WORLD_H
#define INANNA_WORLD_H

#include "Graphics/Graphics.h"

namespace Inanna {
    const float WIDTH = 900;
    const float HEIGHT = 900;
    const float FPS = 60;

    class World {

    public:
        World();
        ~World();

        void Start();

    private:
        bool isExist;

        std::unique_ptr<Graphics> graphics;

        void BringDoom();

        void OnTest();

        void OnRender(float dt);
    };
}

#endif //INANNA_WORLD_H
