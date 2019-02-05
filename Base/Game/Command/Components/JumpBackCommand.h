//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_JUMPBACKCOMMAND_H
#define INANNA_JUMPBACKCOMMAND_H

#include <entityx/Entity.h>
#include "../../Util/Chrono.h"

namespace Inanna {
    struct JumpBackCommand {
        explicit JumpBackCommand(entityx::Entity character) : character(character), time(Chrono::Now()) {}

        entityx::Entity character;
        Uint32 time;
    };
}
#endif //INANNA_JUMPBACKCOMMAND_H
