//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_ORYUCOMMAND_H
#define INANNA_ORYUCOMMAND_H


#include <entityx/Entity.h>
#include "../../Util/Chrono.h"
#include "../../Util/GameKey.h"

namespace Inanna {
    struct OryuCommand {
        explicit OryuCommand(entityx::Entity character, GameKey key) : character(character), key(key), time(Chrono::Now()) {}

        entityx::Entity character;
        Uint32 time;
        GameKey key;
    };
}

#endif //INANNA_ORYUCOMMAND_H
