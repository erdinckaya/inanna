//
// Created by misterdortnal on 26.01.2019.
//

#ifndef INANNA_COMMANDLINK_H
#define INANNA_COMMANDLINK_H


#include <entityx/quick.h>
#include "InputCommand.h"

namespace Inanna {
    struct CommandLink {
        explicit CommandLink(const entityx::Entity &entity, const CommandId &commandId) : entity(entity), commandId(commandId) {}

        entityx::Entity entity;
        CommandId commandId;

        Gallant::Signal2<entityx::Entity, CommandId> onExecuted;
    };
}

#endif //INANNA_COMMANDLINK_H
