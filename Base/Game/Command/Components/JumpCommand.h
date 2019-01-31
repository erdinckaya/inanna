//
// Created by misterdortnal on 31.01.2019.
//

#ifndef INANNA_JUMPCOMMAND_H
#define INANNA_JUMPCOMMAND_H

#include <entityx/Entity.h>
#include "../../Components/UserKey.h"

namespace Inanna {
    struct JumpCommand {
        explicit JumpCommand(entityx::Entity character, const UserKey &userKey) : userKey(userKey),
                                                                                    character(character) {}

        UserKey userKey;
        entityx::Entity character;
    };
}

#endif //INANNA_JUMPCOMMAND_H
