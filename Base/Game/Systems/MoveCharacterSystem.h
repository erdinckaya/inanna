//
// Created by misterdortnal on 23.01.2019.
//

#ifndef INANNA_MOVECHARACTERSYSTEM_H
#define INANNA_MOVECHARACTERSYSTEM_H


#include <entityx/System.h>
#include "../../UI/Components/Position.h"
#include "../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../Components/Character.h"
#include "../Components/MoveCharacter.h"
#include "../../Util/SpriteMacro.h"
#include "../../Game/Command/Components/CommandLink.h"
#include "../Components/Velocity.h"

namespace Inanna {
    struct MoveCharacterSystem : public entityx::System<MoveCharacterSystem> {
        explicit MoveCharacterSystem() = default;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Character, Position, MoveCharacter, Velocity>(
                    [this, dt](entityx::Entity entity, Character &character, Position &position, MoveCharacter &move,
                            Velocity &velocity) {
                        if (entity.component<SpriteAnimation>()->animData != move.animData) {
                            INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(entity, move.animData);
                        }
                        velocity.value = Vecf(25 * move.direction.x, 0);
                    });
        }
    };
}


#endif //INANNA_MOVECHARACTERSYSTEM_H
