//
// Created by Erdınc Kaya on 2019-04-01.
//

#ifndef INANNA_DAMAGERECEIVECOMMANDSYSTEM_H
#define INANNA_DAMAGERECEIVECOMMANDSYSTEM_H


#include <entityx/System.h>
#include "../../../../ThirdParty/boolinq.h"
#include "../Components/JumpCommand.h"
#include "../../Events/LockInput.h"
#include "../../../SpriteAnimation/Event/SpriteIndex.h"
#include "../../../Util/SpriteMacro.h"
#include "../../Components/CharacterState.h"
#include "../Components/DamageReceiveCommand.h"
#include "../../Components/Damage.h"
#include "../../../SpriteAnimation/Components/SpriteZ.h"

using namespace boolinq;

namespace Inanna {
    struct DamageReceiveCommandSystem : public entityx::System<DamageReceiveCommandSystem>, public entityx::Receiver<DamageReceiveCommandSystem>  {

        explicit DamageReceiveCommandSystem() : manager(nullptr) {}

        void configure(entityx::EventManager &events) override {
            manager = &events;
        }

        void ReceiveDamage(DamageReceiveCommand &cmd) {
            if (!cmd.source.has_component<Damage>()) {
                cmd.source.assign<Damage>(cmd.damage);
                cmd.source.component<SpriteZ>()->z = 1;
                cmd.destination.component<SpriteZ>()->z = 0;
            }

            if (!cmd.destination.has_component<Damage>()) {
                cmd.destination.assign<Damage>(-cmd.damage);
            }
        }


        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::vector<DamageReceiveCommand> commands;
            entities.each<DamageReceiveCommand>([&commands](entityx::Entity entity, DamageReceiveCommand &cmd) {
                commands.push_back(cmd);
                entity.destroy();
            });

            commands = from(commands).orderBy([](const DamageReceiveCommand &cmd) { return cmd.time; }).toVector();
            for (auto &cmd : commands) {
                ReceiveDamage(cmd);
            }
        }

    private:
        entityx::EventManager *manager;
    };
}

#endif //INANNA_DAMAGERECEIVECOMMANDSYSTEM_H
