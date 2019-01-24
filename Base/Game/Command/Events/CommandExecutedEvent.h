//
// Created by Erdınc Kaya on 2019-01-24.
//

#ifndef INANNA_COMMANDEXECUTEDEVENT_H
#define INANNA_COMMANDEXECUTEDEVENT_H

#include "../Components/InputCommand.h"

namespace Inanna {
    struct CommandExecutedEvent {
        explicit CommandExecutedEvent(const entityx::Entity &character, const CommandId &id) :
                character(character), id(id) {}

        entityx::Entity character;
        const CommandId id;
    };
}

#endif //INANNA_COMMANDEXECUTEDEVENT_H
