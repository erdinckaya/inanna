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
#include "../Command/Components/CrouchCommand.h"
#include "../Game.h"


using namespace boolinq;

namespace Inanna {
    struct KeyInputSystem : public entityx::System<KeyInputSystem> {

        explicit KeyInputSystem() = default;


        void ClearTimeoutKeys(UserKeyHistory *history) {
            const int size = static_cast<const int>(history->buffer.size());
            const Uint32 TwoSeconds = 2000;
            const Uint32 now = SDL_GetTicks();
            const Uint32 limit = now - TwoSeconds;
            int index = 0;
            for (int i = 0; i < size; ++i) {
                if (history->buffer[i].time <= limit) {
                    index++;
                }
            }

            if (index > 0) {
                history->buffer.erase(history->buffer.begin(), history->buffer.begin() + index);
            }
        }

        GameKey ConvertToGameKey(UserKey &key) {
            if (Game::Instance->Rival.valid()) {
                // TODO: Check relative facing!
            } else {
                switch (key.key) {
                    case SDL_SCANCODE_LEFT:
                        return GameKey::Back_GK;
                    case SDL_SCANCODE_RIGHT:
                        return GameKey::Forward_GK;
                    case SDL_SCANCODE_UP:
                        return GameKey::Jump_GK;
                    case SDL_SCANCODE_DOWN:
                        return GameKey::Crouch_GK;
                    case SDL_SCANCODE_F:
                        return GameKey::LittleFist_GK;
                    case SDL_SCANCODE_K:
                        return GameKey::LittleKick_GK;
                    default:
                        break;
                }
            }
            return InValid;
        }

        void FindSpecialMoves(entityx::Entity entity, std::vector<UserKey> keys) {
            for (auto &userKey : keys) {
                entity.component<UserKeyHistory>()->buffer.push_back(userKey);
            }

            UserKeyHistory* history = entity.component<UserKeyHistory>().get();
            ClearTimeoutKeys(history);
            auto specialKeyDefinations = Game::Instance->KeyPatterns.SpecialMoveKeys;
            std::unordered_map<SpecialMoveKey, int> foundedKeys;
            for (auto &def : specialKeyDefinations) {
                const int size = static_cast<const int>(history->buffer.size());
                for (int i = 0; i < size; ++i) {
                    auto key = ConvertToGameKey(history->buffer[i]);
                    if (key == def.Keys[0]) {
                        int k = 0;
                        for (int j = 0; j < def.Keys.size() && k < size; ++j, ++k) {
                            auto fetchedKey = ConvertToGameKey(history->buffer[j]);
                            if (fetchedKey != def.Keys[k]) {
                                break;
                            }
                        }
                        if (k == def.Keys.size()) {
                            foundedKeys[def.Id] = i;
                        }
                    }
                }
            }

            for (auto& it: foundedKeys) {
                printf("Keys are %d\n", it.first);
            }
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {

            std::vector<UserKey> keys;
            entities.each<UserKey>([&keys](entityx::Entity entity, UserKey &userKey) {
                keys.emplace_back(userKey);
                entity.destroy();
            });

            keys = from(keys).orderBy([](const UserKey &key) { return key.time; }).toVector();

            auto entity = Game::Instance->Player;

            if (entity.valid()) {

                FindSpecialMoves(entity, keys);

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
                        case SDL_SCANCODE_DOWN: {
                            entities.create().assign<CrouchCommand>(entity, userKey);
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
