//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_RUNCOMMANDSYSTEM_H
#define INANNA_RUNCOMMANDSYSTEM_H


#include <entityx/System.h>
#include "../../../../ThirdParty/boolinq.h"
#include "../Components/RunCommand.h"
#include "../../Components/Run.h"
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
            events.subscribe<AbortEvent>(*this);
        }

        void HandleRun(RunCommand &cmd) {
            if (cmd.character.has_component<Run>()) {
                return;
            }

            cmd.character.replace<SpriteLoop>(1, 6);
            float direction = 1.5f;
            if (!cmd.character.component<Facing>()->left) {
                direction = -1.5f;
            }

            cmd.character.replace<Run>(Vecf(direction, 0), 5, AnimationData::KYO_RUN);
            cmd.character.component<CharacterState>()->lock = true;
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
            INANNA_REMOVE_COMPONENT(event.entity, Run)
            INANNA_REMOVE_COMPONENT(event.entity, SpriteLoop)
            INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(event.entity, AnimationData::KYO_IDLE);
            event.entity.component<CharacterState>()->lock = false;
        }

        void receive(const AbortEvent &abortEvent) {
            AbortEvent event = abortEvent;
            if (event.entity.has_component<Run>()) {
                INANNA_REMOVE_COMPONENT(event.entity, Run);
                INANNA_REMOVE_COMPONENT(event.entity, SpriteLoop);
                INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(event.entity, AnimationData::KYO_IDLE);
                event.entity.component<CharacterState>()->lock = false;
            }
        }
    };
}
#endif //INANNA_RUNCOMMANDSYSTEM_H
