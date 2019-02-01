//
// Created by misterdortnal on 27.01.2019.
//

#ifndef INANNA_MOVESTATE_H
#define INANNA_MOVESTATE_H

#include <SDL_types.h>
#include "../Util/MoveStates.h"

namespace Inanna {
    struct MoveState {
        explicit MoveState(const Uint8 &state = MoveStates::IDLE_MS, const bool &lock = false) : state(state),
                                                                                                      lock(lock) {}

        Uint8 state;
        bool lock;

        REFLECT()
    };
}

#endif //INANNA_MOVESTATE_H
