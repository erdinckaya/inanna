//
// Created by misterdortnal on 31.01.2019.
//

#ifndef INANNA_JUMPCHARACTERSYSTEM_H
#define INANNA_JUMPCHARACTERSYSTEM_H


#include <entityx/System.h>
#include "../../UI/Components/Position.h"
#include "../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../Components/Character.h"
#include "../Components/JumpCharacter.h"
#include "../../Util/SpriteMacro.h"
#include "../Events/JumpEnd.h"
#include "../../Util/Math/Physics.h"

namespace Inanna {
    struct JumpCharacterSystem : public entityx::System<JumpCharacterSystem>, entityx::Receiver<JumpCharacterSystem> {

        explicit JumpCharacterSystem() : FLOOR(100), manager(nullptr), LongJumpTimeLimit(100) {}

        void configure(entityx::EventManager &events) override {
            manager = &events;
            events.subscribe<SpriteAnimEnd>(*this);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Character, Position, JumpCharacter, SpriteAnimation, Velocity>(
                    [this, &entities, dt](entityx::Entity entity, Character &character, Position &position,
                                          JumpCharacter &jump, SpriteAnimation &anim, Velocity &velocity) {

                        if (jump.longJump) {
                            INANNA_REPLACE_SPRITE_ANIM_IF_NOT(entity, jump.animData)
                        }

                        if (jump.longJump && Chrono::Now() < jump.startTime + LongJumpTimeLimit &&
                            KeyInput::Instance.WasKeyReleased(GameKey::Up)) {
                            jump.longJump = false;
//                            jump.distance *= 0.5f;
//                            jump.risingTime *= 0.9f;
//                            jump.vX *= 0.5f;
                            velocity.value = Vecf(velocity.value.x, velocity.value.y * 0.6f);
                            auto vy = velocity.value.y;
                            INANNA_REPLACE_SPRITE_ANIM_IF_NOT(entity, AnimationData::KYO_JUMP);
                            anim.animData.speed = 10 * anim.animData.keyFrames.size() / (2 * vy / -Physics::GRAVITY);
                        }

//                        float y = Physics::JumpWithDistanceAndTime(jump.distance, jump.risingTime, jump.totalTime);
//                        jump.totalTime += dt * 0.001f;
//                        auto x = static_cast<float>(dt * 0.1f * jump.vX);
//                        position.position = Vecf(position.position.x + x, y + FLOOR);
//
//
//                        if (position.position.y < FLOOR) {
//                            position.position = Vecf(position.position.x - x, FLOOR);
//                        }

                        if (jump.startTime == Chrono::Now()) {
                            auto vy = 100;
                            anim.animData.speed = 10 * anim.animData.keyFrames.size() / (2 * vy / -Physics::GRAVITY);
                            velocity.value = Vecf(jump.vX, vy);
                        }
                    });
        }

        void receive(const SpriteAnimEnd &spriteAnimEnd) {
            SpriteAnimEnd event = spriteAnimEnd;
            if (event.entity.has_component<JumpCharacter>()) {
                manager->emit<JumpEnd>(event.entity);
            }
        }

    private:
        const int FLOOR;
        const Uint32 LongJumpTimeLimit;
        entityx::EventManager *manager;
    };
}


#endif //INANNA_JUMPCHARACTERSYSTEM_H
