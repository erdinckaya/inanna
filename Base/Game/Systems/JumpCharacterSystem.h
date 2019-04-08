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
                            velocity.value = Vecf(velocity.value.x, velocity.value.y * 0.7f);
                            auto vy = velocity.value.y;
                            INANNA_REPLACE_SPRITE_ANIM_IF_NOT(entity, AnimationData::KYO_JUMP);
                            auto first =  ((jump.vY + vy) * jump.elapsedTime) * 0.5f;
                            const float g = Physics::GRAVITY;
                            float t = velocity.value.y / g;
                            auto second = g * t * t * 0.5f;
                            auto rising = first + second;
                            t += std::sqrt(2 * rising / g) + jump.elapsedTime;

                            anim.animData.speed = 10 * anim.animData.keyFrames.size() / t;
                        }

                        if (jump.started) {
                            jump.elapsedTime += dt * 0.01f;
                        }

                        if (!jump.started) {
                            jump.started = true;
                            jump.startTime = Chrono::Now();
                            auto vy = 100;
                            jump.vY = vy;
                            anim.animData.speed = 10 * anim.animData.keyFrames.size() / (2 * vy / Physics::GRAVITY);
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
