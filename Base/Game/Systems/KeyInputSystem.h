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
#include "../Components/UserKey.h"
#include "../../../ThirdParty/boolinq.h"
#include "../Components/UserKeyHistory.h"
#include "../Command/Components/MoveCommand.h"
#include "../Command/Components/HitCommand.h"

using namespace boolinq;

namespace Inanna {
    struct KeyInputSystem : public entityx::System<KeyInputSystem> {

        explicit KeyInputSystem() = default;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {

            std::vector<UserKey> keys;
            entities.each<UserKey>([&keys](entityx::Entity entity, UserKey &userKey) {
                keys.emplace_back(userKey);
                entity.destroy();
            });

            keys = from(keys).orderBy([](const UserKey &key) { return key.time; }).toVector();

            auto entity = WindowManager::spriteAnimationFactory.character;

            if (entity.valid()) {

                for (auto &userKey : keys) {
                    bool validkKey = false;
                    switch (userKey.key) {
                        case SDL_SCANCODE_LEFT:
                        case SDL_SCANCODE_RIGHT: {
                            entities.create().assign<MoveCommand>(entity, userKey);
                            validkKey = true;
                            break;
                        }
                        case SDL_SCANCODE_K:
                        case SDL_SCANCODE_F: {
                            entities.create().assign<HitCommand>(entity, userKey);
                            validkKey = true;
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }
    };
}


#endif //INANNA_KEYINPUTSYSTEM_H
