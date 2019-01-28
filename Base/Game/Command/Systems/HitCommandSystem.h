//
// Created by Erdınc Kaya on 2019-01-28.
//

#ifndef INANNA_HITCOMMANDSYSTEM_H
#define INANNA_HITCOMMANDSYSTEM_H

#include <entityx/System.h>
#include "../../../../Assets/AnimationData.h"
#include "../../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../../../Util/SpriteMacro.h"
#include "../../Components/MoveState.h"
#include "../../../../ThirdParty/boolinq.h"
#include "../Components/HitCommand.h"
#include "../../Components/Hit.h"

using namespace boolinq;

namespace Inanna {
    struct HitCommandSystem : public entityx::System<HitCommandSystem> {

        void CharacterHit(HitCommand &cmd) {
            auto character = cmd.character;
            switch (cmd.userKey.key) {
                case SDL_SCANCODE_K:
                case SDL_SCANCODE_F: {
                    if (!character.has_component<Hit>()) {
                        character.assign<Hit>(cmd.userKey.key);
                    }
                    break;
                }
                default:
                    break;
            }
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
    };
}
#endif //INANNA_HITCOMMANDSYSTEM_H
