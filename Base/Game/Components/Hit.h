//
// Created by Erdınc Kaya on 2019-01-28.
//

#ifndef INANNA_HIT_H
#define INANNA_HIT_H

#include <SDL_scancode.h>

namespace Inanna {
    struct Hit {
        explicit Hit(const Uint32 &key, SpriteAnimData animData) : key(key), animData(animData) {}
        Uint32 key;
        SpriteAnimData animData;

        REFLECT()
    };
}

#endif //INANNA_HIT_H
