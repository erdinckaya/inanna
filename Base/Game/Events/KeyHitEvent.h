//
// Created by Erdınc Kaya on 2019-01-24.
//

#ifndef INANNA_KEYHITEVENT_H
#define INANNA_KEYHITEVENT_H

#include <SDL_scancode.h>

namespace Inanna {
    struct KeyHitEvent {
        explicit KeyHitEvent(const SDL_Scancode key) : key(key) {}

        SDL_Scancode key;
    };
}


#endif //INANNA_KEYHITEVENT_H
