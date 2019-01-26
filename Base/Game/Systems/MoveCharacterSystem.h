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

namespace Inanna {
    struct MoveCharacterSystem : public entityx::System<MoveCharacterSystem> {
        explicit MoveCharacterSystem() = default;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Character, Position, MoveCharacter, SpriteAnimation>(
                    [this, dt](entityx::Entity entity, Character &character, Position &position, MoveCharacter &move,
                               SpriteAnimation &anim) {
                        double speed = 1000.0 / move.speed;
                        bool isKilled = false;
                        if (move.time >= speed) {
                            move.time = 0;
                            INANNA_REMOVE_COMPONENT(entity, MoveCharacter);
                            INANNA_COMMAND_EXECUTED(entity);
                        } else {
                            move.time += dt;
                        }
                        position.position += move.direction * move.speed;
                    });
        }
    };
}


#endif //INANNA_MOVECHARACTERSYSTEM_H
