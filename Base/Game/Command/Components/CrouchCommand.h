//
// Created by Erdınc Kaya on 2019-01-29.
//

#ifndef INANNA_CROUCHCOMMAND_H
#define INANNA_CROUCHCOMMAND_H

#include <entityx/Entity.h>
#include "../../Components/UserKey.h"

namespace Inanna {
    struct CrouchCommand {
        explicit CrouchCommand(entityx::Entity character, const UserKey &userKey) : userKey(userKey),
                                                                                    character(character) {}

        UserKey userKey;
        entityx::Entity character;
    };
}
#endif //INANNA_CROUCHCOMMAND_H
