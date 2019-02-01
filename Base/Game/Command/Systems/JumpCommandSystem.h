//
// Created by misterdortnal on 31.01.2019.
//

#ifndef INANNA_JUMPCOMMANDSYSTEM_H
#define INANNA_JUMPCOMMANDSYSTEM_H


#include <entityx/System.h>
#include "../Components/CrouchCommand.h"
#include "../../../../ThirdParty/boolinq.h"
#include "../Components/JumpCommand.h"
#include "../../Components/JumpCharacter.h"
#include "../../Components/JumpState.h"
#include "../../Events/JumpEnd.h"
#include "../../Util/Chrono.h"

using namespace boolinq;

namespace Inanna {
    struct JumpCommandSystem : public entityx::System<JumpCommandSystem>, public ex::Receiver<JumpCommandSystem>  {

        void configure(entityx::EventManager &events) override {
            events.subscribe<JumpEnd>(*this);
        }

        void HandleJump(JumpCommand &cmd) {
            if (cmd.character.has_component<JumpCharacter>()) {
                return;
            }
            cmd.character.replace<SpriteIndex>(cmd.character, 4);
            cmd.character.replace<JumpCharacter>(Vecf(0, 3), 5, AnimationData::KYO_JUMP, Chrono::Now());
            cmd.character.component<JumpState>()->state = JumpStates::RISE_JS;
        }


        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::vector<JumpCommand> commands;
            entities.each<JumpCommand>([&commands](entityx::Entity entity, JumpCommand &cmd) {
                commands.push_back(cmd);
                entity.destroy();
            });

            commands = from(commands).orderBy([](const JumpCommand &cmd) { return cmd.userKey.time; }).toVector();
            for (auto &cmd : commands) {
                HandleJump(cmd);
            }
        }

        void receive(const JumpEnd &jumpEnd) {
            JumpEnd event = jumpEnd;
            INANNA_REMOVE_COMPONENT(event.entity, JumpCharacter);
            event.entity.component<JumpState>()->state = JumpStates::IDLE_JS;
            INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(event.entity, AnimationData::KYO_IDLE);
        }
    };
}

#endif //INANNA_JUMPCOMMANDSYSTEM_H
