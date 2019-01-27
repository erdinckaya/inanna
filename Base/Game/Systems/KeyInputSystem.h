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
#include "../Command/Components/InputCommand.h"
#include "../Components/UserKey.h"
#include "../../../ThirdParty/boolinq.h"
#include "../Components/UserKeyContainer.h"
#include "../Command/Components/MoveCommand.h"

using namespace boolinq;

namespace Inanna {
    struct KeyInputSystem : public entityx::System<KeyInputSystem> {

        explicit KeyInputSystem() = default;

        void ClearTimeoutInputs(UserKeyContainer *container) {
            unsigned long size = container->buffer.size();
            auto limit = container->buffer[container->buffer.size() - 1].time - 2000;
            int index = 0;
            for (int i = 0; i < size; ++i) {
                if (container->buffer[i].time <= limit) {
                    index++;
                }
            }

            if (index != 0) {
                container->buffer.erase(container->buffer.begin(), container->buffer.begin() + index);
            }
        }

        void FindKeyPatterns(entityx::EntityManager &entities, entityx::Entity entity, UserKeyContainer *container) {
            if (container == nullptr) {
                return;
            }
            ClearTimeoutInputs(container);

            for (auto &userKey : container->buffer) {
                switch (userKey.key) {
                    case SDL_SCANCODE_LEFT:
                    case SDL_SCANCODE_RIGHT: {
                        entities.create().assign<MoveCommand>(entity, userKey);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        void CreateCommands(entityx::EntityManager &entities, const std::vector<UserKey> &keys) {
            if (!keys.empty()) {
                UserKeyContainer *container = WindowManager::spriteAnimationFactory.character.component<UserKeyContainer>().get();
                for (auto key : keys) {
                    container->buffer.push_back(key);
                }
                FindKeyPatterns(entities, WindowManager::spriteAnimationFactory.character, container);
            }
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {

            std::vector<UserKey> keys;
            entities.each<UserKey>([&keys](entityx::Entity entity, UserKey &userKey) {
                keys.emplace_back(userKey);
                entity.destroy();

//                if (KeyInput::Instance.IsKeyHeld(SDL_SCANCODE_LEFT)) {
//                    entities.create().assign<InputCommand>(entity, SDL_SCANCODE_LEFT, dt);
//                } else if (KeyInput::Instance.IsKeyHeld(SDL_SCANCODE_RIGHT)) {
//                    entities.create().assign<InputCommand>(entity, SDL_SCANCODE_RIGHT, dt);
//                }
//
//                if (KeyInput::Instance.WasKeyReleased(SDL_SCANCODE_LEFT)) {
//                    entities.create().assign<InputCommand>(entity, SDL_SCANCODE_LEFT, dt, false);
//                } else if (KeyInput::Instance.WasKeyReleased(SDL_SCANCODE_RIGHT)) {
//                    entities.create().assign<InputCommand>(entity, SDL_SCANCODE_RIGHT, dt, false);
//                }

//                if (hitKeys[SDL_SCANCODE_F]) {
//                    entities.create().assign<InputCommand>(entity, SDL_SCANCODE_F, dt);
//                } else if (hitKeys[SDL_SCANCODE_K]) {
//                    entities.create().assign<InputCommand>(entity, SDL_SCANCODE_K, dt);
//                }
            });

            keys = from(keys).orderBy([](const UserKey &key) { return key.time; }).toVector();
            CreateCommands(entities, keys);
        }
    };
}


#endif //INANNA_KEYINPUTSYSTEM_H
