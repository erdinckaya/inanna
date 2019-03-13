//
// Created by Erdınc Kaya on 2019-03-13.
//

#ifndef INANNA_CHARACTERSTATE_H
#define INANNA_CHARACTERSTATE_H

#include <SDL_stdinc.h>

namespace Inanna {
    struct CharacterState {
        explicit CharacterState(const Uint8 &state = 0, const bool &lock = false) : state(state), lock(lock) {}

        Uint8 state;
        bool lock;

        REFLECT()
    };
}

#endif //INANNA_CHARACTERSTATE_H
