//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_ORYUCOMMANDSYSTEM_H
#define INANNA_ORYUCOMMANDSYSTEM_H


#include <entityx/System.h>
#include "../Components/CrouchCommand.h"
#include "../../../../ThirdParty/boolinq.h"
#include "../Components/JumpCommand.h"
#include "../../Components/Oryu.h"
#include "../../Components/JumpState.h"
#include "../../Components/MoveState.h"
#include "../../Components/CrouchState.h"
#include "../../Events/OryuEnd.h"
#include "../../Events/MoveEnd.h"
#include "../../Events/JumpEnd.h"
#include "../../Events/RunEnd.h"
#include "../../Events/CrouchEnd.h"
#include "../../Events/LockInput.h"
#include "../../Util/Chrono.h"
#include "../Components/OryuCommand.h"
#include "../../../SpriteAnimation/Event/SpriteIndex.h"
#include "../../../Util/SpriteMacro.h"

using namespace boolinq;

namespace Inanna {
    struct OryuCommandSystem : public entityx::System<OryuCommandSystem>, public entityx::Receiver<OryuCommandSystem>  {

        explicit OryuCommandSystem() : manager(nullptr) {}

        void configure(entityx::EventManager &events) override {
            events.subscribe<OryuEnd>(*this);
            manager = &events;
        }

        void RemoveOthers(entityx::Entity entity) {
            manager->emit<MoveEnd>(entity);
            manager->emit<JumpEnd>(entity);
            manager->emit<RunEnd>(entity);
            manager->emit<CrouchEnd>(entity);
        }

        void HandleOryu(OryuCommand &cmd) {
            if (cmd.character.has_component<Oryu>()) {
                return;
            }
            RemoveOthers(cmd.character);
            manager->emit<LockInput>(cmd.character, true);
            cmd.character.replace<SpriteIndex>(cmd.character, 4);
            cmd.character.replace<Oryu>(AnimationData::KYO_ORYU, Vecf(0, 1), 5);
        }


        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::vector<OryuCommand> commands;
            entities.each<OryuCommand>([&commands](entityx::Entity entity, OryuCommand &cmd) {
                commands.push_back(cmd);
                entity.destroy();
            });

            commands = from(commands).orderBy([](const OryuCommand &cmd) { return cmd.time; }).toVector();
            for (auto &cmd : commands) {
                HandleOryu(cmd);
            }
        }

        void receive(const OryuEnd &oryuEnd) {
            OryuEnd event = oryuEnd;
            INANNA_REMOVE_COMPONENT(event.entity, Oryu);
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
#endif //INANNA_ORYUCOMMANDSYSTEM_H
