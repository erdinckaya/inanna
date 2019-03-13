//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_JUMPBACKSYSTEM_H
#define INANNA_JUMPBACKSYSTEM_H


#include <entityx/System.h>
#include "../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../Components/Character.h"
#include "../../Util/SpriteMacro.h"
#include "../Components/JumpBack.h"
#include "../../SpriteAnimation/Event/SpriteAnimEnd.h"
#include "../Events/JumpBackEnd.h"
#include "../../UI/Components/Position.h"

namespace Inanna {
    struct JumpBackSystem : public entityx::System<JumpBackSystem>, entityx::Receiver<JumpBackSystem> {
        explicit JumpBackSystem() : FLOOR(100), manager(nullptr) {}

        void configure(entityx::EventManager &events) override {
            manager = &events;
            events.subscribe<SpriteAnimEnd>(*this);
            events.subscribe<SpriteIndex>(*this);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Character, Position, JumpBack>(
                    [this, dt](entityx::Entity entity, Character &character, Position &position, JumpBack &jumpBack) {

                        INANNA_REPLACE_SPRITE_ANIM_IF_NOT(entity, jumpBack.animData);
                        double speed = 1000.0 / jumpBack.speed;
                        if (jumpBack.time >= speed) {
                            jumpBack.time = 0;
                        } else {
                            jumpBack.time += dt;
                        }
                        position.position += jumpBack.direction * jumpBack.speed;
                        if (position.position.y < FLOOR) {
                            position.position = Vecf(position.position.x, FLOOR);
                        }
                    });
        }

        void receive(const SpriteAnimEnd &spriteAnimEnd) {
            SpriteAnimEnd event = spriteAnimEnd;
            if (event.entity.has_component<JumpBack>()) {
                manager->emit<JumpBackEnd>(event.entity);
                auto pos = event.entity.component<Position>()->position;
                event.entity.component<Position>()->position = Vecf(pos.x, FLOOR);
            }
        }

        void receive(const SpriteIndex &spriteIndex) {
            SpriteIndex event = spriteIndex;
            if (event.entity.has_component<JumpBack>()) {
                auto d = event.entity.component<JumpBack>()->direction;
                event.entity.component<JumpBack>()->direction = Vecf(d.x, -d.y);
                event.entity.component<JumpState>()->state = JumpStates::FALL_JS;
            }
        }

    private:
        entityx::EventManager *manager;
        const int FLOOR;
    };
}

#endif //INANNA_JUMPBACKSYSTEM_H
