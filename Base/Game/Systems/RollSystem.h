//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_ROLLSYSTEM_H
#define INANNA_ROLLSYSTEM_H


#include <entityx/System.h>
#include "../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../Components/Character.h"
#include "../../Util/SpriteMacro.h"
#include "../../SpriteAnimation/Event/SpriteAnimEnd.h"
#include "../../UI/Components/Position.h"
#include "../Components/Roll.h"
#include "../Events/RollEnd.h"

namespace Inanna {
    struct RollSystem : public entityx::System<RollSystem>, entityx::Receiver<RollSystem> {
        explicit RollSystem() : manager(nullptr) {}

        void configure(entityx::EventManager &events) override {
            manager = &events;
            events.subscribe<SpriteAnimEnd>(*this);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Character, Position, Roll>(
                    [this, dt](entityx::Entity entity, Character &character, Position &position, Roll &roll) {
                        INANNA_REPLACE_SPRITE_ANIM_IF_NOT(entity, roll.animData)
                        position.position += roll.direction * roll.speed;
                    });
        }

        void receive(const SpriteAnimEnd &spriteAnimEnd) {
            SpriteAnimEnd event = spriteAnimEnd;
            if (event.entity.has_component<Roll>()) {
                manager->emit<RollEnd>(event.entity);
            }
        }

    private:
        entityx::EventManager *manager;
    };
}


#endif //INANNA_ROLLSYSTEM_H
