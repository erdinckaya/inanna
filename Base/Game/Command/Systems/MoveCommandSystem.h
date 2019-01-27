//
// Created by misterdortnal on 27.01.2019.
//

#ifndef INANNA_MOVECOMMANDSYSTEM_H
#define INANNA_MOVECOMMANDSYSTEM_H

#include <entityx/System.h>
#include "../Components/MoveCommand.h"
#include "../../../../Assets/AnimationData.h"
#include "../../Components/MoveCharacter.h"
#include "../../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../../../Util/SpriteMacro.h"

using namespace boolinq;

namespace Inanna {
    struct MoveCommandSystem : public entityx::System<MoveCommandSystem>{

        void Move(MoveCommand &cmd) {
            auto character = cmd.character;
            auto animData = AnimationData::KYO_MOVE_BACK;
            int direction = -1;
            if (cmd.userKey.key == SDL_SCANCODE_RIGHT) {
                animData = AnimationData::KYO_MOVE_FORWARD;
                direction = 1;
            }

            if (cmd.userKey.down) {
                character.replace<MoveCharacter>(Vecf(0.75f, 0) * direction, 5);

                if (character.component<SpriteAnimation>()->animData != animData) {
                    INANNA_REPLACE_SPRITE_ANIM(character, animData);
                    auto anim = character.component<SpriteAnimation>();
                    anim->loop = true;
                }
            } else {
                INANNA_REMOVE_COMPONENT(character, MoveCharacter);
                INANNA_REPLACE_SPRITE_ANIM(character, AnimationData::KYO_IDLE);
                auto anim = character.component<SpriteAnimation>();
                anim->loop = true;
            }
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::vector<MoveCommand> commands;
            entities.each<MoveCommand>([&commands](entityx::Entity entity, MoveCommand &cmd) {
                commands.push_back(cmd);
                entity.destroy();
            });

            commands = from(commands).orderBy([](const MoveCommand &cmd) {return cmd.userKey.time;}).toVector();
            for (auto &cmd : commands) {
                Move(cmd);
            }
        }

    private:
        std::set<entityx::Entity, Uint32> lastMoveUpTime;
    };
}

#endif //INANNA_MOVECOMMANDSYSTEM_H
