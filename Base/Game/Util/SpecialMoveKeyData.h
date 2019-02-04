//
// Created by Erdınc Kaya on 2019-01-28.
//

#ifndef INANNA_SPECIALMOVEKEYDATA_H
#define INANNA_SPECIALMOVEKEYDATA_H

#include <string>
#include <vector>
#include <SDL_quit.h>
#include "GameKey.h"
#include "SpecialMoveKey.h"

namespace Inanna {
    struct SpecialMoveKeyData {
        explicit SpecialMoveKeyData(): Id(SpecialMoveKey::Invalid), Duration(0) {}

        SpecialMoveKey Id;
        std::vector<GameKey> Keys;
        Uint32 Duration;
    };
}

#endif //INANNA_SPECIALMOVEKEYDATA_H
