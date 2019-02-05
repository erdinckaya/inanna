//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_RUNCOMMAND_H
#define INANNA_RUNCOMMAND_H

#include <entityx/Entity.h>
#include "../../Components/UserKey.h"

namespace Inanna {
    struct RunCommand {
        explicit RunCommand(entityx::Entity character) : character(character), time(Chrono::Now()) {}

        entityx::Entity character;
        Uint32 time;
    };
}
#endif //INANNA_RUNCOMMAND_H
