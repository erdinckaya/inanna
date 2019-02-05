//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_CROUCHSTATES_H
#define INANNA_CROUCHSTATES_H


#include "../../../ThirdParty/enum.h"
#include <SDL_types.h>

namespace Inanna {
    BETTER_ENUM(CrouchStates, Uint8, Idle = 0, Crouch = 1)
}

#endif //INANNA_CROUCHSTATES_H
