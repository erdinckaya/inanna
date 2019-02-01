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
#include "../Components/MoveState.h"
#include "../Events/JumpEnd.h"

namespace Inanna {
    struct JumpCharacterSystem : public entityx::System<JumpCharacterSystem>, entityx::Receiver<JumpCharacterSystem> {

        explicit JumpCharacterSystem() : FLOOR(100), manager(nullptr), LongJumpTimeLimit(100) {}

        void configure(entityx::EventManager &events) override {
            manager = &events;
            events.subscribe<SpriteIndex>(*this);
            events.subscribe<SpriteAnimEnd>(*this);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Character, Position, JumpCharacter, SpriteAnimation, MoveState>(
                    [this, dt](entityx::Entity entity, Character &character, Position &position, JumpCharacter &jump,
                               SpriteAnimation &anim, MoveState &moveState) {
                        moveState.lock = true;
                        INANNA_REPLACE_SPRITE_ANIM_IF_NOT(entity, jump.animData);
                        if (!jump.longJump && Chrono::Now() > jump.startTime + LongJumpTimeLimit &&
                            KeyInput::Instance.IsKeyHeld(SDL_SCANCODE_UP)) {
                            jump.longJump = true;
                            anim.animData.speed *= 0.5f;
                            jump.direction *= 1.8f;
                        }

                        double speed = 1000.0 / jump.speed;
                        bool isKilled = false;
                        if (jump.time >= speed) {
                            jump.time = 0;
                        } else {
                            jump.time += dt;
                        }

                        position.position += jump.direction * jump.speed;
                        if (position.position.y < FLOOR) {
                            position.position = Vecf(position.position.x, FLOOR);
                        }
                    });
        }

        void receive(const SpriteAnimEnd &spriteAnimEnd) {
            SpriteAnimEnd event = spriteAnimEnd;
            if (event.entity.has_component<JumpCharacter>()) {
                manager->emit<JumpEnd>(event.entity);
                event.entity.component<MoveState>()->lock = false;
            }
        }

        void receive(const SpriteIndex &spriteIndex) {
            SpriteIndex event = spriteIndex;
            if (event.entity.has_component<JumpCharacter>()) {
                event.entity.component<JumpCharacter>()->direction *= -1;
                event.entity.component<JumpState>()->state = JumpStates::FALL_JS;
            }
        }

    private:
        const int FLOOR;
        const Uint32 LongJumpTimeLimit;
        entityx::EventManager *manager;
    };
}


#endif //INANNA_JUMPCHARACTERSYSTEM_H
