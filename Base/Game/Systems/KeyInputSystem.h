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
#include "../Components/JumpCharacter.h"
#include "../Components/Crouch.h"
#include "../../Input/KeyInput.h"
#include "../Components/UserKey.h"
#include "../../../ThirdParty/boolinq.h"
#include "../Components/UserKeyHistory.h"
#include "../Events/AbortEvent.h"
#include "../Command/Components/MoveCommand.h"
#include "../Command/Components/HitCommand.h"
#include "../Command/Components/CrouchCommand.h"
#include "../Command/Components/JumpCommand.h"
#include "../Command/Components/JumpBackCommand.h"
#include "../Command/Components/RunCommand.h"
#include "../Command/Components/RollCommand.h"
#include "../Command/Components/OryuCommand.h"
#include "../Util/Chrono.h"
#include "../Util/CharacterBehaivour.h"
#include "../Game.h"
#include "../Events/LockInput.h"


using namespace boolinq;

namespace Inanna {
    struct KeyInputSystem : public entityx::System<KeyInputSystem>, entityx::Receiver<KeyInputSystem> {

        explicit KeyInputSystem() = default;

        static GameKey ConvertToGameKey(SDL_Scancode key);

        void configure(entityx::EventManager &events) override {
            events.subscribe<LockInput>(*this);
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
                if (HandleSpecialMoves(entities, events, keys, entity)) {
                    return;
                }
                HandleSimpleMoves(entities, events, keys, entity);
            }
        }

        void receive(const LockInput &lockInput) {
            lockedCharacters[lockInput.entity] = lockInput.value;
        }



    private:

        std::tuple<SpecialMoveKey, GameKey> FindSpecialMoves(entityx::Entity entity, std::vector<UserKey> keys);

        bool HandleSpecialMoves(entityx::EntityManager &entities, entityx::EventManager &events,
                                std::vector<UserKey> &keys,
                                entityx::Entity &entity);

        void HandleSimpleMoves(entityx::EntityManager &entities, entityx::EventManager &events,
                               std::vector<UserKey> &keys,
                               entityx::Entity &entity);

        void ClearTimeoutKeys(UserKeyHistory *history);

        std::unordered_map<entityx::Entity, bool> lockedCharacters;
    };
}


#endif //INANNA_KEYINPUTSYSTEM_H
