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
#include "../../Components/MoveState.h"
#include "../../Components/JumpState.h"
#include "../../Util/JumpStates.h"
#include "../../Events/RunEnd.h"
#include "../../Events/MoveEnd.h"

using namespace boolinq;

namespace Inanna {
    struct MoveCommandSystem : public entityx::System<MoveCommandSystem>, entityx::Receiver<MoveCommandSystem> {

        explicit MoveCommandSystem(): manager(nullptr) {}

        void configure(entityx::EventManager &events) override {
            manager = &events;
            events.subscribe<MoveEnd>(*this);
        }

        void Move(entityx::Entity &character, SpriteAnimData &animData, int direction) const {
            character.replace<MoveCharacter>(Vecf(0.75f, 0) * direction, 5, animData);
        }

        void RemoveMove(entityx::Entity &character) const {
            if (character.has_component<MoveCharacter>()) {
                INANNA_REMOVE_COMPONENT(character, MoveCharacter);
                INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(character, AnimationData::KYO_IDLE);
            }
        }

        void Move(MoveCommand &cmd) {
            auto character = cmd.character;

            if (character.has_component<MoveCharacter>() && cmd.userKey.down) {
                return;
            }

            auto animData = AnimationData::KYO_MOVE_BACK;
            int direction = -1;
            if (cmd.userKey.key == SDL_SCANCODE_RIGHT) {
                animData = AnimationData::KYO_MOVE_FORWARD;
                direction = 1;
            }

            if (cmd.userKey.down) {
                Move(character, animData, direction);
            } else {
                RemoveMove(character);
            }
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::vector<MoveCommand> commands;
            entities.each<MoveCommand>([&commands](entityx::Entity entity, MoveCommand &cmd) {
                commands.push_back(cmd);
                entity.destroy();
            });

            commands = from(commands).orderBy([](const MoveCommand &cmd) { return cmd.userKey.time; }).toVector();
            for (auto &cmd : commands) {
                auto jumpState = cmd.character.component<JumpState>()->state;
                auto moveLock = cmd.character.component<MoveState>()->lock;
                if (cmd.character.component<MoveState>()->state == MoveStates::RUN_MS && !cmd.userKey.down) {
                    manager->emit<RunEnd>(cmd.character);
                    return;
                }

                if (jumpState == JumpStates::IDLE_JS) {
                    if (!cmd.userKey.down || !moveLock) {
                        Move(cmd);
                    }
                }
            }
        }

        void receive(const MoveEnd &moveEnd) {
            MoveEnd event = moveEnd;
            if (event.entity.has_component<MoveCharacter>()) {
                RemoveMove(event.entity);
            }
        }
    private:
        entityx::EventManager *manager;
    };
}

#endif //INANNA_MOVECOMMANDSYSTEM_H
