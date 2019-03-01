//
// Created by misterdortnal on 23.01.2019.
//

#ifndef INANNA_KEYINPUTSYSTEM_H
#define INANNA_KEYINPUTSYSTEM_H


#include <entityx/System.h>
#include <map>

#include "../../UI/Components/Position.h"
#include "../Components/Facing.h"
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
#include "../Command/Components/JumpCommand.h"
#include "../Command/Components/JumpBackCommand.h"
#include "../Command/Components/RunCommand.h"
#include "../Command/Components/RollCommand.h"
#include "../Command/Components/OryuCommand.h"
#include "../Util/Chrono.h"
#include "../Game.h"
#include "../Events/LockInput.h"


using namespace boolinq;

namespace Inanna {
    struct KeyInputSystem : public entityx::System<KeyInputSystem>, entityx::Receiver<KeyInputSystem> {

        explicit KeyInputSystem() = default;

        void configure(entityx::EventManager &events) override {
            events.subscribe<LockInput>(*this);
        }


        void ClearTimeoutKeys(UserKeyHistory *history) {
            const int size = static_cast<const int>(history->buffer.size());
            const Uint32 OneSeconds = 1000;
            const Uint32 now = Chrono::Now();
            const Uint32 limit = now - OneSeconds;
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

        static GameKey ConvertToGameKey(SDL_Scancode key) {
            switch (key) {
                case SDL_SCANCODE_LEFT:
                    return Game::Instance->Player.component<Facing>()->left ? GameKey::Back : GameKey::Forward;
                case SDL_SCANCODE_RIGHT:
                    return Game::Instance->Player.component<Facing>()->left ? GameKey::Forward : GameKey::Back;
                case SDL_SCANCODE_UP:
                    return GameKey::Up;
                case SDL_SCANCODE_DOWN:
                    return GameKey::Down;
                case SDL_SCANCODE_F:
                    return GameKey::LittleFist;
                case SDL_SCANCODE_K:
                    return GameKey::LittleKick;
                case SDL_SCANCODE_D:
                    return GameKey::BigFist;
                case SDL_SCANCODE_L:
                    return GameKey::BigKick;
                default:
                    break;
            }
            return GameKey::InValid;
        }

        std::tuple<SpecialMoveKey, GameKey> FindSpecialMoves(entityx::Entity entity, std::vector<UserKey> keys) {
            for (auto &userKey : keys) {
                entity.component<UserKeyHistory>()->buffer.push_back(userKey);
            }



            UserKeyHistory *history = entity.component<UserKeyHistory>().get();
            ClearTimeoutKeys(history);
            auto specialKeyDefinations = Game::Instance->Patterns.SpecialMoveKeys;
            std::vector<SpecialMoveKey> foundedKeys;
            GameKey lastKey = GameKey::InValid;
            std::vector<UserKey> userKeys;

            auto downBuffer = from(history->buffer).where([](const UserKey &u) { return u.down; }).
                    select([](const UserKey &u) { return u; }).toVector();

            for (auto &def : specialKeyDefinations) {
                const int size = static_cast<const int>(downBuffer.size());
                for (int i = 0; i < size; ++i) {
                    auto key = GameKey::_from_integral(downBuffer[i].key);
                    if (key == def.Keys[0]) {
                        int k = 0;
                        for (int j = i; k < def.Keys.size() && j < size; ++j, ++k) {
                            auto fetchedKey = GameKey::_from_integral(downBuffer[j].key);
                            lastKey = fetchedKey;

                            if (def.Keys[k] == +GameKey::Hit) {
                                if (!IS_HIT(fetchedKey)) {
                                    break;
                                }

                            } else if (fetchedKey != def.Keys[k]) {
                                break;
                            }

                            userKeys.push_back(downBuffer[j]);
                        }
                        if (k == def.Keys.size()) {
                            foundedKeys.push_back(def.Id);
                            for (auto userKey : userKeys) {
                                for (int l = 0; l < history->buffer.size(); ++l) {
                                    if (userKey == history->buffer[l]) {
                                        history->buffer.erase(history->buffer.begin() + l);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            return std::make_tuple(foundedKeys.empty() ? +SpecialMoveKey::Invalid : foundedKeys[0], lastKey);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {

            std::vector<UserKey> keys;
            entities.each<UserKey>([&](entityx::Entity entity, UserKey &userKey) {
                if (!lockedCharacters[entity]) {
                    keys.emplace_back(userKey);
                }
                entity.destroy();
            });


            keys = from(keys).orderBy([](const UserKey &key) { return key.time; }).toVector();

            auto entity = Game::Instance->Player;
            if (lockedCharacters[entity]) {
                return;
            }

            if (entity.valid()) {
                auto result = FindSpecialMoves(entity, keys);
                auto specialKey = std::get<0>(result);
                if (specialKey != +SpecialMoveKey::Invalid) {
                    printf("SpecialKey is %s\n", specialKey._to_string());
                    switch (specialKey) {
                        case SpecialMoveKey::JumpBack:
                            entities.create().assign<JumpBackCommand>(entity);
                            break;
                        case SpecialMoveKey::Run:
                            entities.create().assign<RunCommand>(entity);
                            break;
                        case SpecialMoveKey::Oryu:
                            entities.create().assign<OryuCommand>(entity, std::get<1>(result));
                            break;
                        default:
                            break;
                    }

                    return;
                }

                if (KeyInput::Instance.IsKeyHeld(SDL_SCANCODE_LEFT) && KeyInput::Instance.IsKeyHeld(SDL_SCANCODE_F) &&
                    KeyInput::Instance.IsKeyHeld(SDL_SCANCODE_K)) {
                    entities.create().assign<RollCommand>(entity, false);
                    return;
                } else if (KeyInput::Instance.IsKeyHeld(SDL_SCANCODE_F) &&
                           KeyInput::Instance.IsKeyHeld(SDL_SCANCODE_K)) {
                    entities.create().assign<RollCommand>(entity, true);
                    return;
                }

                for (auto &userKey : keys) {
                    bool validkKey = false;
                    auto k = GameKey::_from_integral(userKey.key);
                    switch (k) {
                        case GameKey::Back:
                        case GameKey::Forward: {
                            entities.create().assign<MoveCommand>(entity, userKey);
                            validkKey = true;
                            break;
                        }
                        case GameKey::LittleFist:
                        case GameKey::LittleKick:
                        case GameKey::BigFist:
                        case GameKey::BigKick: {
                            entities.create().assign<HitCommand>(entity, userKey);
                            validkKey = true;
                            break;
                        }
                        case GameKey::Down: {
                            entities.create().assign<CrouchCommand>(entity, userKey);
                            validkKey = true;
                            break;
                        }
                        case GameKey::Up: {
                            entities.create().assign<JumpCommand>(entity, userKey);
                            validkKey = true;
                            break;
                        }
                        default:
                            break;
                    }
                }

                if (KeyInput::Instance.IsKeyHeld(SDL_SCANCODE_UP)) {
                    UserKey key(SDL_SCANCODE_UP, Chrono::Now(), true);
                    entities.create().assign<JumpCommand>(entity, key);
                } else if (KeyInput::Instance.IsKeyHeld(SDL_SCANCODE_DOWN)) {
                    UserKey key(SDL_SCANCODE_DOWN, Chrono::Now(), true);
                    entities.create().assign<CrouchCommand>(entity, key);
                } else if (KeyInput::Instance.IsKeyHeld(SDL_SCANCODE_LEFT)) {
                    UserKey key(SDL_SCANCODE_LEFT, Chrono::Now(), true);
                    entities.create().assign<MoveCommand>(entity, key);
                } else if (KeyInput::Instance.IsKeyHeld(SDL_SCANCODE_RIGHT)) {
                    UserKey key(SDL_SCANCODE_RIGHT, Chrono::Now(), true);
                    entities.create().assign<MoveCommand>(entity, key);
                }
            }
        }

        void receive(const LockInput &lockInput) {
            lockedCharacters[lockInput.entity] = lockInput.value;
        }

    private:
        std::unordered_map<entityx::Entity, bool> lockedCharacters;
    };
}


#endif //INANNA_KEYINPUTSYSTEM_H
