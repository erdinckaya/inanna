//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_CROUCHSTATE_H
#define INANNA_CROUCHSTATE_H

#include <SDL_types.h>
#include "../Util/CrouchStates.h"

namespace Inanna {
    struct CrouchState {
        explicit CrouchState(const Uint8 &state = CrouchStates::Idle, const bool &lock = false) : state(state),
                                                                                                 lock(lock) {}

        Uint8 state;
        bool lock;

        REFLECT()
    };
}
#endif //INANNA_CROUCHSTATE_H
