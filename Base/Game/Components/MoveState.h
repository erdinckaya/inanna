//
// Created by misterdortnal on 27.01.2019.
//

#ifndef INANNA_MOVESTATE_H
#define INANNA_MOVESTATE_H

#include <SDL_types.h>
#include "../Util/MoveStates.h"

namespace Inanna {
    struct MoveState {
        explicit MoveState(const MoveStates &state = MoveStates::IDLE_MS, const bool &lock = false) : state(state),
                                                                                                      lock(lock) {}

        MoveStates state;
        bool lock;
    };
}

#endif //INANNA_MOVESTATE_H
