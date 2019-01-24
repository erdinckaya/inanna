//
// Created by Erdınc Kaya on 2019-01-24.
//

#ifndef INANNA_MOVELOGIC_H
#define INANNA_MOVELOGIC_H

#include "../Command/Components/InputCommand.h"
#include "../../../Assets/AnimationData.h"

namespace Inanna {
    struct MoveLogic {
        static void Move(const InputCommand &cmd) {
            auto entity = cmd.character;
            auto animData = AnimationData::KYO_MOVE_BACK;
            int direction = -1;
            if (cmd.key == SDL_SCANCODE_RIGHT) {
                animData = AnimationData::KYO_MOVE_FORWARD;
                direction = 1;
            }

            if (cmd.down) {
                entity.replace<MoveCharacter>(Vecf(0.75f, 0) * direction, 5);

                if (entity.component<SpriteAnimation>()->animData != animData) {
                    INANNA_REPLACE_SPRITE_ANIM(entity, animData);
                    auto anim = entity.component<SpriteAnimation>();
                    anim->loop = true;
                } else {
                    entity.component<SpriteAnimation>()->loop = true;
                }
            } else {
                INANNA_REMOVE_COMPONENT(entity, MoveCharacter);
            }
        }
    };
}

#endif //INANNA_MOVELOGIC_H
