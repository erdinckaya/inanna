//
// Created by Erdınc Kaya on 2019-01-29.
//

#ifndef INANNA_CROUCHSYSTEM_H
#define INANNA_CROUCHSYSTEM_H


#include <entityx/System.h>
#include "../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../Components/Character.h"
#include "../../Util/SpriteMacro.h"
#include "../Components/MoveState.h"
#include "../Components/Crouch.h"
#include "../Components/CrouchState.h"

namespace Inanna {
    struct CrouchSystem : public entityx::System<CrouchSystem> {
        explicit CrouchSystem() = default;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Character, Crouch>([this, dt](entityx::Entity entity, Character &character, Crouch &crouch) {
                if (entity.component<CrouchState>()->lock) {
                    return;
                }
                INANNA_REPLACE_SPRITE_ANIM_IF_NOT(entity, AnimationData::KYO_CROUCH);
                entity.component<SpriteAnimation>()->stayAtLastFrame = true;
            });
        }
    };
}

#endif //INANNA_CROUCHSYSTEM_H
