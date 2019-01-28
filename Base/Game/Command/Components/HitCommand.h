//
// Created by Erdınc Kaya on 2019-01-28.
//

#ifndef INANNA_HITCOMMAND_H
#define INANNA_HITCOMMAND_H

#include <entityx/Entity.h>
#include "../../Components/UserKey.h"

namespace Inanna {
    struct HitCommand {
        explicit HitCommand(entityx::Entity character, const UserKey &userKey) : userKey(userKey),
                                                                                  character(character) {}

        UserKey userKey;
        entityx::Entity character;
    };
}
#endif //INANNA_HITCOMMAND_H
