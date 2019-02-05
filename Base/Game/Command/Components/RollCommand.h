//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_ROLLCOMMAND_H
#define INANNA_ROLLCOMMAND_H


#include <entityx/Entity.h>
#include "../../Util/Chrono.h"

namespace Inanna {
    struct RollCommand {
        explicit RollCommand(entityx::Entity character, const bool &forward) : forward(forward), character(character), time(Chrono::Now()) {}

        bool forward;
        Uint32 time;
        entityx::Entity character;
    };
}

#endif //INANNA_ROLLCOMMAND_H
