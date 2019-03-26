//
// Created by Erdınc Kaya on 2019-01-28.
//

#ifndef INANNA_HITCOMMAND_H
#define INANNA_HITCOMMAND_H

#include <entityx/Entity.h>
#include "../../Components/UserKey.h"
#include "../../Util/CharacterBehaivour.h"

namespace Inanna {
    struct HitCommand {
        explicit HitCommand(entityx::Entity character, const UserKey &userKey, const CharacterBehaviour &state) : userKey(userKey),
                                                                                  character(character), state(state) {}

        UserKey userKey;
        entityx::Entity character;
        CharacterBehaviour state;
    };
}
#endif //INANNA_HITCOMMAND_H
