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
#include "../Events/KeyHitEvent.h"
#include "../Command/Components/InputCommand.h"


namespace Inanna {
    struct KeyInputSystem : public entityx::System<KeyInputSystem>, public ex::Receiver<KeyInputSystem> {

        void configure(ex::EventManager &events) override {
            events.subscribe<KeyHitEvent>(*this);
        }

        explicit KeyInputSystem() = default;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {

            entities.each<Character>([&](entityx::Entity entity, Character &character) {
                if (KeyInput::Instance.IsKeyHeld(SDL_SCANCODE_LEFT)) {
                    entities.create().assign<InputCommand>(entity, SDL_SCANCODE_LEFT, dt);
                } else if (KeyInput::Instance.IsKeyHeld(SDL_SCANCODE_RIGHT)) {
                    entities.create().assign<InputCommand>(entity, SDL_SCANCODE_RIGHT, dt);
                }

                if (KeyInput::Instance.WasKeyReleased(SDL_SCANCODE_LEFT)) {
                    entities.create().assign<InputCommand>(entity, SDL_SCANCODE_LEFT, dt, false);
                } else if (KeyInput::Instance.WasKeyReleased(SDL_SCANCODE_RIGHT)) {
                    entities.create().assign<InputCommand>(entity, SDL_SCANCODE_RIGHT, dt, false);
                }

                if (hitKeys[SDL_SCANCODE_F]) {
                    entities.create().assign<InputCommand>(entity, SDL_SCANCODE_F, dt);
                } else if (hitKeys[SDL_SCANCODE_K]) {
                    entities.create().assign<InputCommand>(entity, SDL_SCANCODE_K, dt);
                }
            });

            hitKeys.clear();
        }


        void receive(const KeyHitEvent &keyHitEvent) {
            hitKeys[keyHitEvent.key] = true;
        }

    private:
        std::map<SDL_Scancode, bool> hitKeys;
    };
}


#endif //INANNA_KEYINPUTSYSTEM_H
