//
// Created by Erdınc Kaya on 2019-01-29.
//

#ifndef INANNA_CROUCHCOMMANDSYSTEM_H
#define INANNA_CROUCHCOMMANDSYSTEM_H


#include <entityx/System.h>
#include "../../Components/Crouch.h"
#include "../../Events/CrouchEnd.h"
#include "../Components/CrouchCommand.h"
#include "../../../../ThirdParty/boolinq.h"

using namespace boolinq;

namespace Inanna {
    struct CrouchCommandSystem : public entityx::System<CrouchCommandSystem>, entityx::Receiver<CrouchCommandSystem> {

        void configure(entityx::EventManager &events) override {
            events.subscribe<CrouchEnd>(*this);
            events.subscribe<AbortEvent>(*this);
        }

        void CrouchCharacter(CrouchCommand &cmd) {
            if (cmd.character.has_component<Crouch>()) {
                return;
            }
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

        void receive(const CrouchEnd &crouchEnd) {
            CrouchEnd event = crouchEnd;
            if (event.entity.has_component<Crouch>()) {
                INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(event.entity, AnimationData::KYO_IDLE);
                INANNA_REMOVE_COMPONENT(event.entity, Crouch);
            }
        }

        void receive(const AbortEvent &abortEvent) {
            AbortEvent event = abortEvent;
            if (event.entity.has_component<Crouch>()) {
                INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(event.entity, AnimationData::KYO_IDLE);
                INANNA_REMOVE_COMPONENT(event.entity, Crouch);
            }
        }
    };
}


#endif //INANNA_CROUCHCOMMANDSYSTEM_H
