//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_ROLLCOMMANDSYSTEM_H
#define INANNA_ROLLCOMMANDSYSTEM_H

#include <entityx/System.h>
#include "../../../../ThirdParty/boolinq.h"
#include "../../Util/Chrono.h"
#include "../Components/JumpBackCommand.h"
#include "../../Components/Roll.h"
#include "../../Components/JumpState.h"
#include "../../Components/MoveState.h"
#include "../../Events/RollEnd.h"
#include "../../Events/CrouchEnd.h"
#include "../../../../Assets/AnimationData.h"
#include "../../../Util/SpriteMacro.h"
#include "../Components/RollCommand.h"
#include "../../../Util/Math/Vec2.h"
#include "../../Components/CrouchState.h"

using namespace boolinq;

namespace Inanna {
    struct RollCommandSystem : public entityx::System<RollCommandSystem>, public entityx::Receiver<RollCommandSystem> {
        explicit RollCommandSystem() : manager(nullptr) {}

        void configure(entityx::EventManager &events) override {
            manager = &events;
            events.subscribe<RollEnd>(*this);
        }

        void RemoveOthers(entityx::Entity entity) {
            manager->emit<MoveEnd>(entity);
            manager->emit<JumpEnd>(entity);
            manager->emit<RunEnd>(entity);
            manager->emit<CrouchEnd>(entity);
        }

        void HandleJumpBack(RollCommand &cmd) {
            if (cmd.character.has_component<Roll>()
                || cmd.character.has_component<Hit>()
                || cmd.character.has_component<JumpCharacter>()) {
                return;
            }

            RemoveOthers(cmd.character);
            manager->emit<LockInput>(cmd.character, true);
            auto direction = cmd.forward ? 1 : -1;
            auto animData = cmd.forward ? AnimationData::KYO_ROLL_FORWARD : AnimationData::KYO_ROLL_BACKWARD;
            cmd.character.replace<Roll>(animData, Vecf(1, 0) * direction, 5);
            cmd.character.component<JumpState>()->lock = true;
            cmd.character.component<MoveState>()->lock = true;
            cmd.character.component<CrouchState>()->lock = true;
        }


        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::vector<RollCommand> commands;
            entities.each<RollCommand>([&commands](entityx::Entity entity, RollCommand &cmd) {
                commands.push_back(cmd);
                entity.destroy();
            });

            commands = from(commands).orderBy([](const RollCommand &cmd) { return cmd.time; }).toVector();
            for (auto &cmd : commands) {
                HandleJumpBack(cmd);
            }
        }

        void receive(const RollEnd &rollEnd) {
            RollEnd event = rollEnd;
            INANNA_REMOVE_COMPONENT(event.entity, Roll);
            event.entity.component<JumpState>()->state = JumpStates::IDLE_JS;
            event.entity.component<JumpState>()->lock = false;
            event.entity.component<MoveState>()->lock = false;
            event.entity.component<CrouchState>()->lock = false;
            INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(event.entity, AnimationData::KYO_IDLE);
            manager->emit<LockInput>(event.entity, false);
        }

    private:
        entityx::EventManager *manager;
    };
}
#endif //INANNA_ROLLCOMMANDSYSTEM_H
