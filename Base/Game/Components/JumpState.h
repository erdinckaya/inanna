//
// Created by misterdortnal on 31.01.2019.
//

#ifndef INANNA_JUMPSTATE_H
#define INANNA_JUMPSTATE_H


#include <SDL_types.h>
#include "../Util/JumpStates.h"

namespace Inanna {
    struct JumpState {
        explicit JumpState(const JumpStates &state = JumpStates::IDLE_JS, const bool &lock = false) : state(state),
                                                                                                      lock(lock) {}

        Uint8 state;
        bool lock;

        REFLECT()
    };
}

#endif //INANNA_JUMPSTATE_H
