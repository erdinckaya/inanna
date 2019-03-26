//
// Created by Erdınc Kaya on 2019-03-13.
//

#include "KeyInputSystem.h"


bool Inanna::KeyInputSystem::HandleSpecialMoves(entityx::EntityManager &entities, entityx::EventManager &events,
                                                std::vector<UserKey> &keys,
                                                entityx::Entity &entity) {
    auto result = FindSpecialMoves(entity, keys);
    auto specialKey = std::get<0>(result);
    if (specialKey != +SpecialMoveKey::Invalid) {
        printf("SpecialKey is %s\n", specialKey._to_string());
        events.emit<AbortEvent>(entity);
        switch (specialKey) {
            case SpecialMoveKey::JumpBack:
                entity.component<CharacterState>()->state = CharacterBehaviour::JumpBack;
                entities.create().assign<JumpBackCommand>(entity);
                break;
            case SpecialMoveKey::Run:
                entity.component<CharacterState>()->state = CharacterBehaviour::Run;
                entities.create().assign<RunCommand>(entity);
                break;
            case SpecialMoveKey::Oryu:
                entity.component<CharacterState>()->state = CharacterBehaviour::Oryu;
                entities.create().assign<OryuCommand>(entity, std::get<1>(result));
                break;
            default:
                break;
        }

        return true;
    }
    return false;
}

void Inanna::KeyInputSystem::HandleSimpleMoves(entityx::EntityManager &entities, entityx::EventManager &events,
                                               std::vector<UserKey> &keys,
                                               entityx::Entity &entity) {
    auto characterState = entity.component<CharacterState>();
    auto oldState = characterState->state;
    auto state = CharacterBehaviourUtil::GetCharacterBehaviour(entity);
    if (oldState != state && state == +CharacterBehaviour::Idle) {
        events.emit<AbortEvent>(entity);
    }

    if (characterState->lock) {
        return;
    }

    if (oldState != state) {
        events.emit<AbortEvent>(entity);
    }


    switch (state) {
        case CharacterBehaviour::MoveLeft: {
            auto genKey = ConvertToGameKey(SDL_SCANCODE_LEFT);
            entities.create().assign<MoveCommand>(entity,
                                                  UserKey(genKey._to_integral(), Chrono::Now(), true));
            break;
        }
        case CharacterBehaviour::MoveRight: {
            auto genKey = ConvertToGameKey(SDL_SCANCODE_RIGHT);
            entities.create().assign<MoveCommand>(entity,
                                                  UserKey(genKey._to_integral(), Chrono::Now(), true));
            break;
        }
        case CharacterBehaviour::Crouch: {
            auto genKey = ConvertToGameKey(SDL_SCANCODE_DOWN);
            entities.create().assign<CrouchCommand>(entity,
                                                    UserKey(genKey._to_integral(), Chrono::Now(), true));
            break;
        }
        case CharacterBehaviour::Jump: {
            auto genKey = ConvertToGameKey(SDL_SCANCODE_UP);
            entities.create().assign<JumpCommand>(entity,
                                                  UserKey(genKey._to_integral(), Chrono::Now(), true));
            break;
        }
        case CharacterBehaviour::JumpLeft: {
            auto genKey = ConvertToGameKey(SDL_SCANCODE_LEFT);
            entities.create().assign<JumpCommand>(entity,
                                                  UserKey(genKey._to_integral(), Chrono::Now(), true));
            break;
        }
        case CharacterBehaviour::JumpRight: {
            auto genKey = ConvertToGameKey(SDL_SCANCODE_RIGHT);
            entities.create().assign<JumpCommand>(entity,
                                                  UserKey(genKey._to_integral(), Chrono::Now(), true));
            break;
        }
        case CharacterBehaviour::Idle: {
            if (oldState != state) {
                events.emit<AbortEvent>(entity);
            }
            break;
        }
        default:
            break;
    }
    entity.component<CharacterState>()->state = state;
}

bool Inanna::KeyInputSystem::HandleSimpleHits(entityx::EntityManager &entities, entityx::EventManager &events,
                                              std::vector<UserKey> &keys,
                                              entityx::Entity &entity) {
    auto downBuffer = from(keys).where([](const UserKey &u) {
        auto key = GameKey::_from_integral(u.key);
        return u.down && key != +GameKey::InValid && IS_HIT(key);
    }).select([](const UserKey &u) { return u; }).toVector();

    if (downBuffer.empty()) {
        return false;
    }

    auto characterState = entity.component<CharacterState>();
    auto state = CharacterBehaviour::_from_integral(characterState->state);

    // For just one hit
    auto key = GameKey::_from_integral(downBuffer[0].key);


    bool canHit = true;

    switch (state) {
        case CharacterBehaviour::Idle:
        case CharacterBehaviour::MoveLeft:
        case CharacterBehaviour::MoveRight: {
            switch (key) {
                case GameKey::LittleFist: {
                    state = CharacterBehaviour::LittleFist;
                    break;
                }
                case GameKey::LittleKick: {
                    state = CharacterBehaviour::LittleKick;
                    break;
                }
                case GameKey::BigFist: {
                    state = CharacterBehaviour::BigFist;
                    break;
                }
                case GameKey::BigKick: {
                    state = CharacterBehaviour::BigKick;
                    break;
                }
                default: {
                    canHit = false;
                    break;
                }

            }
            break;
        }

        case CharacterBehaviour::Crouch: {
            switch (key) {
                case GameKey::LittleFist: {
                    state = CharacterBehaviour::CrouchLittleFist;
                    break;
                }
                case GameKey::LittleKick: {
                    state = CharacterBehaviour::CrouchLittleKick;
                    break;
                }
                case GameKey::BigFist: {
                    state = CharacterBehaviour::CrouchBigFist;
                    break;
                }
                case GameKey::BigKick: {
                    state = CharacterBehaviour::CrouchBigKick;
                    break;
                }
                default: {
                    canHit = false;
                    break;
                }

            }
            break;
        }
        case CharacterBehaviour::Jump:
        case CharacterBehaviour::JumpLeft:
        case CharacterBehaviour::JumpRight: {
            switch (key) {
                case GameKey::LittleFist: {
                    state = CharacterBehaviour::JumpLittleFist;
                    break;
                }
                case GameKey::LittleKick: {
                    state = CharacterBehaviour::JumpLittleKick;
                    break;
                }
                case GameKey::BigFist: {
                    state = CharacterBehaviour::JumpBigFist;
                    break;
                }
                case GameKey::BigKick: {
                    state = CharacterBehaviour::JumpBigKick;
                    break;
                }
                default: {
                    canHit = false;
                    break;
                }

            }
            break;
        }
        default:
            break;
    }

    if (canHit) {
        entities.create().assign<HitCommand>(entity, UserKey(key._to_integral(), Chrono::Now(), true), state);
//        entity.component<CharacterState>()->state = state;
        return true;
    }

    return false;
}


std::tuple<Inanna::SpecialMoveKey, Inanna::GameKey>
Inanna::KeyInputSystem::FindSpecialMoves(entityx::Entity entity, std::vector<UserKey> keys) {
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


Inanna::GameKey Inanna::KeyInputSystem::ConvertToGameKey(SDL_Scancode key) {
    switch (key) {
        case SDL_SCANCODE_LEFT:
            return Game::Instance->Player.component<Facing>()->left ? GameKey::Back : GameKey::Forward;
        case SDL_SCANCODE_RIGHT:
            return Game::Instance->Player.component<Facing>()->left ? GameKey::Forward : GameKey::Back;
        case SDL_SCANCODE_UP:
            return GameKey::Up;
        case SDL_SCANCODE_DOWN:
            return GameKey::Down;
        case SDL_SCANCODE_A:
            return GameKey::LittleFist;
        case SDL_SCANCODE_S:
            return GameKey::LittleKick;
        case SDL_SCANCODE_Z:
            return GameKey::BigFist;
        case SDL_SCANCODE_X:
            return GameKey::BigKick;
        default:
            break;
    }
    return GameKey::InValid;
}


void Inanna::KeyInputSystem::ClearTimeoutKeys(Inanna::UserKeyHistory *history) {
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