//
// Created by Erdınc Kaya on 2019-01-28.
//

#ifndef INANNA_HIT_H
#define INANNA_HIT_H

#include <SDL_scancode.h>

namespace Inanna {
    struct Hit {
        explicit Hit(const SDL_Scancode &key) : key(key) {}
        SDL_Scancode key;
    };
}

#endif //INANNA_HIT_H
