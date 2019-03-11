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
            auto animData = AnimationData::KYO_JUMP;
            int direction = 0;
            auto key = GameKey::_from_integral(cmd.userKey.key);
            if (key == +GameKey::Forward) {
                animData = AnimationData::KYO_JUMP_FORWARD;
                if (cmd.character.component<Facing>()->left) {
                    direction = 1;
                } else {
                    direction = -1;
                }
            } else if (key == +GameKey::Back) {
                animData = AnimationData::KYO_JUMP_BACKWARD;
                if (cmd.character.component<Facing>()->left) {
                    direction = -1;
                } else {
                    direction = 1;
                }
            }

            cmd.character.replace<SpriteIndex>(cmd.character, 4);
            cmd.character.replace<JumpCharacter>(Vecf(direction, 3), 5, animData, Chrono::Now());
            cmd.character.component<JumpState>()->state = JumpStates::RISE_JS;
            INANNA_REMOVE_COMPONENT(cmd.character, MoveCharacter);
        }


        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::vector<JumpCommand> commands;
            entities.each<JumpCommand>([&commands](entityx::Entity entity, JumpCommand &cmd) {
                commands.push_back(cmd);
                entity.destroy();
            });

            commands = from(commands).orderBy([](const JumpCommand &cmd) { return cmd.userKey.time; }).toVector();
            for (auto &cmd : commands) {
                if (!cmd.character.component<JumpState>()->lock) {
                    HandleJump(cmd);
                }
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
