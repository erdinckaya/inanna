//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_JUMPBACKCOMMANDSYSTEM_H
#define INANNA_JUMPBACKCOMMANDSYSTEM_H


#include <entityx/System.h>
#include "../../../../ThirdParty/boolinq.h"
#include "../Components/JumpBackCommand.h"
#include "../../Events/JumpBackEnd.h"
#include "../../Components/JumpBack.h"
#include "../../../../Assets/AnimationData.h"
#include "../../../Util/SpriteMacro.h"

using namespace boolinq;

namespace Inanna {
    struct JumpBackCommandSystem : public entityx::System<JumpBackCommandSystem>, public entityx::Receiver<JumpBackCommandSystem> {

        void configure(entityx::EventManager &events) override {
            events.subscribe<JumpBackEnd>(*this);
            manager = &events;
        }

        void HandleJumpBack(JumpBackCommand &cmd) {
            if (cmd.character.has_component<JumpBack>()) {
                return;
            }
            cmd.character.replace<SpriteIndex>(cmd.character, 2);
            int direction = -1;
            if (!cmd.character.component<Facing>()->left) {
                direction = 1;
            }
            cmd.character.replace<JumpBack>(AnimationData::KYO_JUMP_BACK, Vecf(direction, 0.5f), 8);
            cmd.character.component<CharacterState>()->lock = true;
            manager->emit<LockInput>(cmd.character, true);
        }


        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::vector<JumpBackCommand> commands;
            entities.each<JumpBackCommand>([&commands](entityx::Entity entity, JumpBackCommand &cmd) {
                commands.push_back(cmd);
                entity.destroy();
            });

            commands = from(commands).orderBy([](const JumpBackCommand &cmd) { return cmd.time; }).toVector();
            for (auto &cmd : commands) {
                HandleJumpBack(cmd);
            }
        }

        void receive(const JumpBackEnd &jumpBackEnd) {
            JumpBackEnd event = jumpBackEnd;
            INANNA_REMOVE_COMPONENT(event.entity, JumpBack);
            INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(event.entity, AnimationData::KYO_IDLE);
            event.entity.component<CharacterState>()->lock = false;
            manager->emit<LockInput>(event.entity, false);
        }

    private:
        entityx::EventManager *manager;
    };
}

#endif //INANNA_JUMPBACKCOMMANDSYSTEM_H
