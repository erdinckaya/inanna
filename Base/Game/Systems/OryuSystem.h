//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_ORYUSYSTEM_H
#define INANNA_ORYUSYSTEM_H


#include <entityx/System.h>
#include "../../UI/Components/Position.h"
#include "../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../Components/Character.h"
#include "../../Util/SpriteMacro.h"
#include "../../SpriteAnimation/Event/SpriteIndex.h"
#include "../../SpriteAnimation/Event/SpriteAnimEnd.h"
#include "../Util/Chrono.h"
#include "../Components/Oryu.h"
#include "../Events/OryuEnd.h"

namespace Inanna {
    struct OryuSystem : public entityx::System<OryuSystem>, entityx::Receiver<OryuSystem> {

        explicit OryuSystem() : FLOOR(100), manager(nullptr), LongJumpTimeLimit(100) {}

        void configure(entityx::EventManager &events) override {
            manager = &events;
            events.subscribe<SpriteIndex>(*this);
            events.subscribe<SpriteAnimEnd>(*this);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Character, Position, Oryu, SpriteAnimation>(
                    [this, dt](entityx::Entity entity, Character &character, Position &position, Oryu &oryu,
                               SpriteAnimation &anim) {

                        INANNA_REPLACE_SPRITE_ANIM_IF_NOT(entity, oryu.animData);
                        double speed = 1000.0 / oryu.speed;
                        bool isKilled = false;
                        if (oryu.time >= speed) {
                            oryu.time = 0;
                        } else {
                            oryu.time += dt;
                        }

                        position.position += oryu.direction * oryu.speed;
                        if (position.position.y < FLOOR) {
                            position.position = Vecf(position.position.x, FLOOR);
                        }
                    });
        }

        void receive(const SpriteAnimEnd &spriteAnimEnd) {
            SpriteAnimEnd event = spriteAnimEnd;
            if (event.entity.has_component<Oryu>()) {
                manager->emit<OryuEnd>(event.entity);
                auto pos = event.entity.component<Position>()->position;
                event.entity.component<Position>()->position = Vecf(pos.x, FLOOR);
            }
        }

        void receive(const SpriteIndex &spriteIndex) {
            SpriteIndex event = spriteIndex;
            if (event.entity.has_component<Oryu>()) {
                event.entity.component<Oryu>()->direction *= -1;
            }
        }

    private:
        const int FLOOR;
        const Uint32 LongJumpTimeLimit;
        entityx::EventManager *manager;
    };
}



#endif //INANNA_ORYUSYSTEM_H
