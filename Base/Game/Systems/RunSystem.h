//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_RUNSYSTEM_H
#define INANNA_RUNSYSTEM_H

#include <entityx/System.h>
#include "../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../Components/Character.h"
#include "../../Util/SpriteMacro.h"
#include "../Components/MoveState.h"
#include "../../SpriteAnimation/Event/SpriteAnimEnd.h"
#include "../../UI/Components/Position.h"
#include "../../SpriteAnimation/Event/SpriteIndex.h"
#include "../Components/Run.h"
#include "../Events/RunEnd.h"

namespace Inanna {
    struct RunSystem : public entityx::System<RunSystem>, entityx::Receiver<RunSystem> {
        explicit RunSystem() : manager(nullptr) {}

        void configure(entityx::EventManager &events) override {
            manager = &events;
            events.subscribe<SpriteAnimEnd>(*this);
            events.subscribe<SpriteIndex>(*this);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Character, MoveState, Position, Run>(
                    [this, dt](entityx::Entity entity, Character &character, MoveState &moveState,
                               Position &position,
                               Run &run) {

                        INANNA_REPLACE_SPRITE_ANIM_IF_NOT(entity, run.animData);
                        double speed = 1000.0 / run.speed;
                        if (run.time >= speed) {
                            run.time = 0;
                        } else {
                            run.time += dt;
                        }
                        position.position += run.direction * run.speed;
                    });
        }

        void receive(const SpriteAnimEnd &spriteAnimEnd) {
            SpriteAnimEnd event = spriteAnimEnd;
            if (event.entity.has_component<Run>()) {
                manager->emit<RunEnd>(event.entity);
            }
        }

        void receive(const SpriteIndex &spriteIndex) {
            SpriteIndex event = spriteIndex;
            if (event.entity.has_component<Run>()) {
//                auto d = event.entity.component<JumpBack>()->direction;
//                event.entity.component<JumpBack>()->direction = Vecf(d.x, -d.y);
//                event.entity.component<JumpState>()->state = JumpStates::FALL_JS;
                event.entity.component<SpriteAnimation>()->frameIndex = 1;
            }
        }

    private:
        entityx::EventManager *manager;
    };
}

#endif //INANNA_RUNSYSTEM_H
