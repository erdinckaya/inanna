//
// Created by Erdınc Kaya on 2019-04-01.
//

#ifndef INANNA_DAMAGECOMMANDSYSTEM_H
#define INANNA_DAMAGECOMMANDSYSTEM_H


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
#include "../../Events/DamageEnd.h"

using namespace boolinq;

namespace Inanna {
    struct DamageCommandSystem
            : public entityx::System<DamageCommandSystem>, public entityx::Receiver<DamageCommandSystem> {

        explicit DamageCommandSystem() : manager(nullptr) {}

        void configure(entityx::EventManager &events) override {
            manager = &events;
            manager->subscribe<DamageEnd>(*this);
        }

        void HandleDamage(entityx::EntityManager &entities, DamageReceiveCommand &cmd) {
            if (cmd.destination.has_component<Damage>() || cmd.damage == 0) {
                return;
            }

            cmd.destination.component<CharacterState>()->lock = false;
            auto startPos = cmd.destination.component<Position>()->position.x;
            cmd.destination.assign<Damage>(cmd.source, cmd.destination, cmd.damage,
                                           AnimationData::KYO_DAMAGE_TAKEN_NORMAL, startPos);

            cmd.source.component<SpriteZ>()->z = 1;
            cmd.destination.component<SpriteZ>()->z = 0;
        }


        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::vector<DamageReceiveCommand> commands;
            entities.each<DamageReceiveCommand>([&commands](entityx::Entity entity, DamageReceiveCommand &cmd) {
                commands.push_back(cmd);
                entity.destroy();
            });

            commands = from(commands).orderBy([](const DamageReceiveCommand &cmd) { return cmd.time; }).toVector();
            for (auto &cmd : commands) {
                HandleDamage(entities, cmd);
            }
        }

        void receive(const DamageEnd &damageEnd) {
            DamageEnd event = damageEnd;
            INANNA_REMOVE_COMPONENT(event.entity, Damage);
            INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(event.entity, AnimationData::KYO_IDLE);
            event.entity.component<CharacterState>()->lock = false;
        }

    private:
        entityx::EventManager *manager;
    };
}

#endif //INANNA_DAMAGECOMMANDSYSTEM_H
