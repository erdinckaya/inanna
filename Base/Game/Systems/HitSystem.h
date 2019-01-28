//
// Created by Erdınc Kaya on 2019-01-28.
//

#ifndef INANNA_HITSYSTEM_H
#define INANNA_HITSYSTEM_H


#include <entityx/System.h>
#include "../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../Components/Character.h"
#include "../../Util/SpriteMacro.h"
#include "../../Game/Command/Components/CommandLink.h"
#include "../Components/Hit.h"
#include "../Components/MoveState.h"

namespace Inanna {
    struct HitSystem : public entityx::System<HitSystem> {
        explicit HitSystem() = default;

        static void OnHitFinish(entityx::Entity ent) {
            ent.component<MoveState>()->lock = false;
            ent.remove<CommandLink>();
            ent.remove<Hit>();
            INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(ent, AnimationData::KYO_IDLE);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Character, MoveState, SpriteAnimation, Hit>(
                    [this, dt](entityx::Entity entity, Character &character, MoveState &moveState,
                               SpriteAnimation &anim,
                               Hit &hit) {
                        entity.component<MoveState>()->lock = true;
                        switch (hit.key) {
                            case SDL_SCANCODE_F: {
                                INANNA_REPLACE_SPRITE_ANIM_IF_NOT(entity, AnimationData::KYO_LITTLE_FIST);
                                entity.replace<CommandLink>(entity)->onExecuted.Connect(&HitSystem::OnHitFinish);
                                break;
                            }
                            case SDL_SCANCODE_K: {
                                INANNA_REPLACE_SPRITE_ANIM_IF_NOT(entity, AnimationData::KYO_LITTLE_KICK);
                                entity.replace<CommandLink>(entity)->onExecuted.Connect(&HitSystem::OnHitFinish);
                                break;
                            }
                            default:
                                break;
                        }
                    });
        }
    };
}

#endif //INANNA_HITSYSTEM_H
