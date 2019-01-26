//
// Created by Erdınc Kaya on 2019-01-25.
//

#ifndef INANNA_HITLOGIC_H
#define INANNA_HITLOGIC_H

#include "../Command/Components/InputCommand.h"
#include "../../UI/WindowManager.h"
#include "../Command/Events/CommandExecutedEvent.h"
#include "../../Util/SpriteMacro.h"
#include "../../SpriteAnimation/Components/SpriteAnimation.h"

namespace Inanna {
    struct HitLogic {

        static void HitComplete(entityx::Entity character, CommandId id) {
            WindowManager::spriteAnimationFactory.events.emit<CommandExecutedEvent>(character, id);
        }

        static void Hit(InputCommand &cmd) {
            auto entity = cmd.character;
            entity.replace<CommandLink>(cmd.character, cmd.id);
            entity.component<CommandLink>()->onExecuted.Connect(&HitLogic::HitComplete);
            switch (cmd.key) {
                case SDL_SCANCODE_F:{
                    bool isReplaced = false;
                    INANNA_REPLACE_SPRITE_ANIM_IF_NOT(cmd.character, AnimationData::KYO_LITTLE_FIST);
                    break;
                }
                case SDL_SCANCODE_K:{
                    INANNA_REPLACE_SPRITE_ANIM_IF_NOT(cmd.character, AnimationData::KYO_LITTLE_FIST);

                    break;
                }
                default: break;
            }
        }
    };
}

#endif //INANNA_HITLOGIC_H
