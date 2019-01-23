//
// Created by misterdortnal on 23.01.2019.
//

#ifndef INANNA_KEYINPUTSYSTEM_H
#define INANNA_KEYINPUTSYSTEM_H


#include <entityx/System.h>
#include "../../UI/Components/Position.h"
#include "../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../Components/Character.h"
#include "../Components/MoveCharacter.h"
#include "../../Input/KeyInput.h"

namespace Inanna {
    struct KeyInputSystem : public entityx::System<KeyInputSystem> {
        explicit KeyInputSystem() = default;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Character>([this](entityx::Entity entity, Character &character) {
                if (KeyInput::Instance.IsKeyHeld(SDL_SCANCODE_LEFT)) {
                    entity.replace<MoveCharacter>(Vecf(-1, 0), 5);

                    if (entity.component<SpriteAnimation>()->animData != AnimationData::KYO_MOVE_BACK) {
                        entity.remove<SpriteAnimation>();
                        auto anim = entity.assign<SpriteAnimation>(AnimationData::KYO_MOVE_BACK);
                        anim->loop = true;
                    } else {
                        entity.component<SpriteAnimation>()->loop = true;
                    }
                }

                if (KeyInput::Instance.WasKeyReleased(SDL_SCANCODE_LEFT)) {
                    if (entity.has_component<MoveCharacter>()) {
                        entity.remove<MoveCharacter>();

                        entity.remove<SpriteAnimation>();
                        entity.assign<SpriteAnimation>(AnimationData::KYO_IDLE);
                    }
                }

                if (KeyInput::Instance.IsKeyHeld(SDL_SCANCODE_RIGHT)) {
                    entity.replace<MoveCharacter>(Vecf(1, 0), 5);
                    if (entity.component<SpriteAnimation>()->animData != AnimationData::KYO_MOVE_FORWARD) {
                        entity.remove<SpriteAnimation>();
                        auto anim = entity.assign<SpriteAnimation>(AnimationData::KYO_MOVE_FORWARD);
                        anim->loop = true;
                    } else {
                        entity.component<SpriteAnimation>()->loop = true;
                    }
                }

                if (KeyInput::Instance.WasKeyReleased(SDL_SCANCODE_RIGHT)) {
                    if (entity.has_component<MoveCharacter>()) {
                        entity.remove<MoveCharacter>();

                        entity.remove<SpriteAnimation>();
                        entity.assign<SpriteAnimation>(AnimationData::KYO_IDLE);
                    }
                }
            });
        }
    };
}


#endif //INANNA_KEYINPUTSYSTEM_H
