//
// Created by Erdınc Kaya on 2019-03-13.
//

#ifndef INANNA_CHARACTERSTATE_H
#define INANNA_CHARACTERSTATE_H

#include <SDL_stdinc.h>

namespace Inanna {
    struct CharacterState {
        explicit CharacterState(const int &state = 0, const bool &lock = false) : state(state), lock(lock) {}

        int state;
        bool lock;

        void SetState(int state) {
            this->state = state;
        }

        REFLECT()
    };
}

#endif //INANNA_CHARACTERSTATE_H
