//
// Created by Erdınc Kaya on 2019-01-29.
//

#ifndef INANNA_CROUCHCOMMANDSYSTEM_H
#define INANNA_CROUCHCOMMANDSYSTEM_H


#include <entityx/System.h>
#include "../../Components/Crouch.h"
#include "../Components/CrouchCommand.h"
#include "../../../../ThirdParty/boolinq.h"

using namespace boolinq;

namespace Inanna {
    struct CrouchCommandSystem : public entityx::System<CrouchCommandSystem> {

        void CrouchCharacter(CrouchCommand &cmd) {
            cmd.character.replace<Crouch>(cmd.userKey.down);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::vector<CrouchCommand> commands;
            entities.each<CrouchCommand>([&commands](entityx::Entity entity, CrouchCommand &cmd) {
                commands.push_back(cmd);
                entity.destroy();
            });

            commands = from(commands).orderBy([](const CrouchCommand &cmd) { return cmd.userKey.time; }).toVector();
            for (auto &cmd : commands) {
                CrouchCharacter(cmd);
            }
        }
    };
}


#endif //INANNA_CROUCHCOMMANDSYSTEM_H
