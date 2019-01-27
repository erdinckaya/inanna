//
// Created by misterdortnal on 27.01.2019.
//

#ifndef INANNA_MOVECOMMAND_H
#define INANNA_MOVECOMMAND_H

#include "../../Components/UserKey.h"

namespace Inanna {
    struct MoveCommand {
        explicit MoveCommand(entityx::Entity character, const UserKey &userKey) : userKey(userKey),
                                                                                  character(character) {}

        UserKey userKey;
        entityx::Entity character;
    };
}

#endif //INANNA_MOVECOMMAND_H
