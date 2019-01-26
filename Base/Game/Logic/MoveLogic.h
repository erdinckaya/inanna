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
            bool success = false;
            auto entity = cmd.character;
            auto animData = AnimationData::KYO_MOVE_BACK;
            int direction = -1;
            if (cmd.key == SDL_SCANCODE_RIGHT) {
                animData = AnimationData::KYO_MOVE_FORWARD;
                direction = 1;
            }

            if (cmd.down) {

                if (!entity.has_component<MoveCharacter>()) {
                    entity.assign<MoveCharacter>(Vecf(0.75f, 0) * direction, 5);

                    entity.replace<CommandLink>(cmd.character, cmd.id);
                    entity.component<CommandLink>()->onExecuted.Connect(&MoveLogic::MoveComplete);

                    if (entity.component<SpriteAnimation>()->animData != animData) {
                        INANNA_REPLACE_SPRITE_ANIM(entity, animData);
                        auto anim = entity.component<SpriteAnimation>();
                        anim->loop = true;

                    } else {
                        entity.component<SpriteAnimation>()->loop = true;
                    }
                    success = true;
                }
            } else {
                INANNA_REMOVE_COMPONENT(entity, MoveCharacter);
                MoveComplete(cmd.character, cmd.id);
                success = true;
            }

            if (!success) {
                MoveComplete(cmd.character, cmd.id);
            }
        }
    };
}

#endif //INANNA_MOVELOGIC_H
