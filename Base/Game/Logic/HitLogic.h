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

            entity.component<SpriteAnimation>()->commandId = cmd.id;
            entity.component<SpriteAnimation>()->onComplete.Bind(&HitLogic::HitComplete);
        }
    };
}

#endif //INANNA_HITLOGIC_H
