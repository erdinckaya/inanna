//
// Created by misterdortnal on 23.01.2019.
//

#ifndef INANNA_MOVECHARACTERSYSTEM_H
#define INANNA_MOVECHARACTERSYSTEM_H


#include <entityx/System.h>
#include "../../UI/Components/Position.h"
#include "../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../Components/Character.h"
#include "../../Util/SpriteMacro.h"
#include "../Events/CollisionEvent.h"

namespace Inanna {
    struct MoveCharacterSystem : public entityx::System<MoveCharacterSystem>, entityx::Receiver<MoveCharacterSystem> {
        explicit MoveCharacterSystem() = default;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Character, Position, MoveCharacter>(
                    [this, dt](entityx::Entity entity, Character &character, Position &position, MoveCharacter &move) {
                        if (entity.component<SpriteAnimation>()->animData != move.animData) {
                            INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(entity, move.animData)
                        }
                        position.position += move.direction * move.speed;
                    });
        }
    };
}


#endif //INANNA_MOVECHARACTERSYSTEM_H
