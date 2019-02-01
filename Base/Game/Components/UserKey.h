//
// Created by misterdortnal on 27.01.2019.
//

#ifndef INANNA_USERKEY_H
#define INANNA_USERKEY_H

#include <SDL_scancode.h>

namespace Inanna {
    struct UserKey {
        explicit UserKey() : key(SDL_SCANCODE_UNKNOWN), time(0), down(false) {}

        explicit UserKey(int key, Uint32 time, bool down) : key(key), time(time), down(down) {}

        int key;
        Uint32 time;
        bool down;

        std::string ToString() {
            return std::to_string(key) + ", " + std::to_string(time) + ", " + std::to_string(down);
        }

        REFLECT()
    };
}

#endif //INANNA_USERKEY_H
