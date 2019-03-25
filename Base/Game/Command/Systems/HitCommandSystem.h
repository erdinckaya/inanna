//
// Created by Erdınc Kaya on 2019-01-28.
//

#ifndef INANNA_HITCOMMANDSYSTEM_H
#define INANNA_HITCOMMANDSYSTEM_H

#include <entityx/System.h>
#include "../../../../Assets/AnimationData.h"
#include "../../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../../../Util/SpriteMacro.h"
#include "../../../../ThirdParty/boolinq.h"
#include "../Components/HitCommand.h"
#include "../../Components/Hit.h"
#include "../../Events/HitEnd.h"

using namespace boolinq;

namespace Inanna {
    struct HitCommandSystem : public entityx::System<HitCommandSystem>, entityx::Receiver<HitCommandSystem> {

        void configure(entityx::EventManager &events) override {
            manager = &events;
            events.subscribe<HitEnd>(*this);
        }

        void CharacterHit(HitCommand &cmd) {
            if (cmd.character.has_component<Hit>()) {
                return;
            }

            cmd.character.assign<Hit>(cmd.userKey.key);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::vector<HitCommand> commands;
            entities.each<HitCommand>([&commands](entityx::Entity entity, HitCommand &cmd) {
                commands.push_back(cmd);
                entity.destroy();
            });

            commands = from(commands).orderBy([](const HitCommand &cmd) { return cmd.userKey.time; }).toVector();
            for (auto &cmd : commands) {
                CharacterHit(cmd);
            }
        }

        void receive(const HitEnd &hitEvent) {
            HitEnd event = hitEvent;
            if (event.entity.has_component<Hit>()) {
                INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(event.entity, AnimationData::KYO_IDLE);
                INANNA_REMOVE_COMPONENT(event.entity, Hit);
            }
        }

    private:
        entityx::EventManager *manager;
    };
}
#endif //INANNA_HITCOMMANDSYSTEM_H
