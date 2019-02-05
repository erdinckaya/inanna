//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_RUNCOMMANDSYSTEM_H
#define INANNA_RUNCOMMANDSYSTEM_H


#include <entityx/System.h>
#include "../../../../ThirdParty/boolinq.h"
#include "../../Util/Chrono.h"
#include "../Components/RunCommand.h"
#include "../../Components/Run.h"
#include "../../Components/JumpState.h"
#include "../../Components/MoveState.h"
#include "../../Components/CrouchState.h"
#include "../../../../Assets/AnimationData.h"
#include "../../../Util/SpriteMacro.h"
#include "../../../SpriteAnimation/Event/SpriteIndex.h"
#include "../../Events/RunEnd.h"
#include "../../../SpriteAnimation/Components/SpriteLoop.h"

using namespace boolinq;

namespace Inanna {
    struct RunCommandSystem : public entityx::System<RunCommandSystem>, public entityx::Receiver<RunCommandSystem> {

        void configure(entityx::EventManager &events) override {
            events.subscribe<RunEnd>(*this);
        }

        void HandleRun(RunCommand &cmd) {
            if (cmd.character.has_component<Run>()) {
                return;
            }

            cmd.character.replace<SpriteLoop>(1, 6);
            cmd.character.replace<Run>(Vecf(1.5f, 0), 5, AnimationData::KYO_RUN);
            cmd.character.component<JumpState>()->lock = true;
            cmd.character.component<JumpState>()->state = JumpStates::RISE_JS;
            cmd.character.component<MoveState>()->lock = true;
            cmd.character.component<MoveState>()->state = MoveStates::RUN_MS;
            cmd.character.component<CrouchState>()->lock = true;
            cmd.character.component<CrouchState>()->state = CrouchStates::Idle;
        }


        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::vector<RunCommand> commands;
            entities.each<RunCommand>([&commands](entityx::Entity entity, RunCommand &cmd) {
                commands.push_back(cmd);
                entity.destroy();
            });

            commands = from(commands).orderBy([](const RunCommand &cmd) { return cmd.time; }).toVector();
            for (auto &cmd : commands) {
                HandleRun(cmd);
            }
        }

        void receive(const RunEnd &runEnd) {
            RunEnd event = runEnd;
            INANNA_REMOVE_COMPONENT(event.entity, Run);
            INANNA_REMOVE_COMPONENT(event.entity, SpriteLoop);
            event.entity.component<JumpState>()->lock = false;
            event.entity.component<JumpState>()->state = JumpStates::IDLE_JS;
            event.entity.component<MoveState>()->lock = false;
            event.entity.component<MoveState>()->state = MoveStates::IDLE_MS;
            event.entity.component<CrouchState>()->lock = false;
            event.entity.component<CrouchState>()->state = CrouchStates::Idle;
            INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(event.entity, AnimationData::KYO_IDLE);
        }
    };
}
#endif //INANNA_RUNCOMMANDSYSTEM_H
