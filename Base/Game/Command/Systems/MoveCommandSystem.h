//
// Created by misterdortnal on 27.01.2019.
//

#ifndef INANNA_MOVECOMMANDSYSTEM_H
#define INANNA_MOVECOMMANDSYSTEM_H

#include <entityx/System.h>
#include "../Components/MoveCommand.h"
#include "../../../../Assets/AnimationData.h"
#include "../../Components/MoveCharacter.h"
#include "../../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../../../Util/SpriteMacro.h"
#include "../../Events/RunEnd.h"
#include "../../Events/MoveEnd.h"
#include "../../Events/AbortEvent.h"

using namespace boolinq;

namespace Inanna {
    struct MoveCommandSystem : public entityx::System<MoveCommandSystem>, entityx::Receiver<MoveCommandSystem> {

        explicit MoveCommandSystem(): manager(nullptr) {}

        void configure(entityx::EventManager &events) override {
            manager = &events;
            events.subscribe<MoveEnd>(*this);
            events.subscribe<AbortEvent>(*this);
        }

        void Move(entityx::Entity &character, SpriteAnimData &animData, int direction) const {
            character.replace<MoveCharacter>(Vecf(1, 0) * direction, 5, animData);
        }

        void RemoveMove(entityx::Entity &character) const {
            if (character.has_component<MoveCharacter>()) {
                INANNA_REMOVE_COMPONENT(character, MoveCharacter);
                INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(character, AnimationData::KYO_IDLE);
                character.component<Velocity>()->value = Vecf(0, 0);
            }
        }

        void Move(MoveCommand &cmd) {
            auto character = cmd.character;

            if (character.has_component<MoveCharacter>()) {
                return;
            }

            auto animData = AnimationData::KYO_MOVE_BACK;
            int direction = -1;
            if (cmd.userKey.key == GameKey::Forward) {
                animData = AnimationData::KYO_MOVE_FORWARD;
                direction = 1;
                if (!cmd.character.component<Facing>()->left) {
                    direction = -1;
                }
            } else if (cmd.userKey.key == GameKey::Back) {
                if (!cmd.character.component<Facing>()->left) {
                    direction = 1;
                }
            }

            Move(character, animData, direction);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::vector<MoveCommand> commands;
            entities.each<MoveCommand>([&commands](entityx::Entity entity, MoveCommand &cmd) {
                commands.push_back(cmd);
                entity.destroy();
            });

            commands = from(commands).orderBy([](const MoveCommand &cmd) { return cmd.userKey.time; }).toVector();
            for (auto &cmd : commands) {
                Move(cmd);
            }
        }

        void receive(const MoveEnd &moveEnd) {
            MoveEnd event = moveEnd;
            if (event.entity.has_component<MoveCharacter>()) {
                RemoveMove(event.entity);
            }
        }

        void receive(const AbortEvent &abortEnd) {
            AbortEvent event = abortEnd;
            if (event.entity.has_component<MoveCharacter>()) {
                RemoveMove(event.entity);
            }
        }
    private:
        entityx::EventManager *manager;
    };
}

#endif //INANNA_MOVECOMMANDSYSTEM_H
