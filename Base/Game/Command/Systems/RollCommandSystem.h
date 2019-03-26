//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_ROLLCOMMANDSYSTEM_H
#define INANNA_ROLLCOMMANDSYSTEM_H

#include <entityx/System.h>
#include "../../../../ThirdParty/boolinq.h"
#include "../../Util/Chrono.h"
#include "../../Components/Roll.h"
#include "../../Events/RollEnd.h"
#include "../../../../Assets/AnimationData.h"
#include "../../../Util/SpriteMacro.h"
#include "../Components/RollCommand.h"
#include "../../../Util/Math/Vec2.h"

using namespace boolinq;

namespace Inanna {
    struct RollCommandSystem : public entityx::System<RollCommandSystem>, public entityx::Receiver<RollCommandSystem> {
        explicit RollCommandSystem() : manager(nullptr) {}

        void configure(entityx::EventManager &events) override {
            manager = &events;
            events.subscribe<RollEnd>(*this);
        }

        void HandleJumpBack(RollCommand &cmd) {
            if (cmd.character.has_component<Roll>()) {
                return;
            }

            cmd.character.replace<CharacterState>(CharacterBehaviour::Roll, true);
            manager->emit<LockInput>(cmd.character, true);
            auto direction = cmd.forward ? 1 : -1;
            if (!cmd.character.component<Facing>()->left) {
                direction *= -1;
            }

            auto animData = cmd.forward ? AnimationData::KYO_ROLL_FORWARD : AnimationData::KYO_ROLL_BACKWARD;
            cmd.character.replace<Roll>(animData, Vecf(1, 0) * direction, 5);
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
            INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(event.entity, AnimationData::KYO_IDLE);
            manager->emit<LockInput>(event.entity, false);
            event.entity.replace<CharacterState>(CharacterBehaviour::Idle);
        }

    private:
        entityx::EventManager *manager;
    };
}
#endif //INANNA_ROLLCOMMANDSYSTEM_H
