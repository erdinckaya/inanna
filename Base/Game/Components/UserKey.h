//
// Created by misterdortnal on 27.01.2019.
//

#ifndef INANNA_USERKEY_H
#define INANNA_USERKEY_H

#include <SDL_scancode.h>

namespace Inanna {
    struct UserKey {
        explicit UserKey(SDL_Scancode key, Uint32 time, bool down, bool hit) : key(key), time(time), down(down),
                                                                               hit(hit) {}

        SDL_Scancode key;
        Uint32 time;
        bool down;
        bool hit;
    };
}

#endif //INANNA_USERKEY_H
