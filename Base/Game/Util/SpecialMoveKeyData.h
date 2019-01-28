//
// Created by Erdınc Kaya on 2019-01-28.
//

#ifndef INANNA_SPECIALMOVEKEYDATA_H
#define INANNA_SPECIALMOVEKEYDATA_H

#include <string>
#include <vector>
#include <SDL_quit.h>
#include "GameKey.h"

namespace Inanna {
    struct SpecialMoveKeyData {
        std::string Id;
        std::vector<GameKey> Keys;
        Uint32 duration;
    };
}

#endif //INANNA_SPECIALMOVEKEYDATA_H
