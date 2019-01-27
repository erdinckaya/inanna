//
// Created by Erdınc Kaya on 2019-01-24.
//

#ifndef INANNA_MOVELOGIC_H
#define INANNA_MOVELOGIC_H

#include "../Command/Components/InputCommand.h"
#include "../../../Assets/AnimationData.h"
#include "../Command/Events/CommandExecutedEvent.h"

namespace Inanna {
    struct MoveLogic {

        static void MoveComplete(entityx::Entity character, CommandId id) {
            WindowManager::spriteAnimationFactory.events.emit<CommandExecutedEvent>(character, id);
        }

        static void Move(InputCommand &cmd) {

        }
    };
}

#endif //INANNA_MOVELOGIC_H
