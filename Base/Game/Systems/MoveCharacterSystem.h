//
// Created by Erdınc Kaya on 2019-01-23.
//

#ifndef INANNA_MOVECHARACTERSYSTEM_H
#define INANNA_MOVECHARACTERSYSTEM_H

#include <entityx/System.h>
#include "../../UI/Components/Position.h"
#include "../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../Components/MoveCharacter.h"

namespace Inanna {
    struct MoveCharacterSystem : public entityx::System<MoveCharacterSystem> {
        explicit MoveCharacterSystem() = default;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Position, MoveCharacter, SpriteAnimation>(
                    [this](entityx::Entity entity, Position &position, MoveCharacter &move, SpriteAnimation &anim) {
                        if (anim.animData != AnimationData::KYO_MOVE_BACK || anim.animData != AnimationData::KYO_MOVE_FORWARD) {
                            entity.replace<SpriteAnimation>(AnimationData::KYO_IDLE);
                        }

                        position.position += Vecf(0,0);
                    });
        }
    };
}

#endif //INANNA_MOVECHARACTERSYSTEM_H
