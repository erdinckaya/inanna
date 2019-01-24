//
// Created by Erdınc Kaya on 2019-01-24.
//

#ifndef INANNA_INPUTCOMMANDSYSTEM_H
#define INANNA_INPUTCOMMANDSYSTEM_H

#include <entityx/entityx.h>
#include "../../Components/Character.h"
#include "../Components/InputCommand.h"

#include "../../Components/MoveCharacter.h"
#include "../../../SpriteAnimation/Components/SpriteAnimation.h"
#include "../../../Util/SpriteMacro.h"
#include "../../Logic/MoveLogic.h"

#include "../../../../ThirdParty/boolinq.h"
#include "../Events/CommandExecutedEvent.h"

using namespace boolinq;

namespace Inanna {
    struct InputCommandSystem
            : public entityx::System<InputCommandSystem>, public entityx::Receiver<InputCommandSystem> {
        explicit InputCommandSystem() = default;

        void configure(ex::EventManager &events) override {
            events.subscribe<CommandExecutedEvent>(*this);
        }

        void Consume() {
            auto cmd = queue.front();
            queue.pop();
            switch (cmd.key) {
                case SDL_SCANCODE_RIGHT:
                case SDL_SCANCODE_LEFT: {
                    MoveLogic::Move(cmd);
                    break;
                }
                case SDL_SCANCODE_F: {
                    INANNA_REPLACE_SPRITE_ANIM_IF_NOT(cmd.character, AnimationData::KYO_LITTLE_FIST);
                    break;
                }
                case SDL_SCANCODE_K: {
                    INANNA_REPLACE_SPRITE_ANIM_IF_NOT(cmd.character, AnimationData::KYO_LITTLE_KICK);
                    break;
                }
                default:
                    break;
            }
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::vector<InputCommand> list;
            auto hasInterrupt = false;
            entities.each<InputCommand>([this, &list, &hasInterrupt](entityx::Entity entity, InputCommand &cmd) {
                // TODO ERDINC TEST! DELETE THIS LATER
                character = cmd.character;
                if (cmd.interrupt) {
                    list.clear();
                    hasInterrupt = true;
                }
                list.emplace_back(cmd);
                entity.destroy();
            });

            if (hasInterrupt) {
                Clear();
            }

            auto commands = from(list).orderBy([](const InputCommand &cmd) { return cmd.id; }).toVector();
            auto size = commands.size();
            auto queueSize = queue.size();
            for (int i = 0; i < size; ++i) {
                queue.emplace(commands[i]);
            }

            if (queueSize == 0 && !queue.empty()) {
                Consume();
            }
        }

        void receive(const CommandExecutedEvent &event) {
            Consume();
            if (queue.empty()) {
                INANNA_REPLACE_SPRITE_ANIM_IF_NOT(character, AnimationData::KYO_IDLE);
            }
        }

        void Clear() {
            std::queue<InputCommand> empty;
            std::swap(queue, empty);
        }

        std::queue<InputCommand> queue;
        entityx::Entity character;
    };
}

#endif //INANNA_INPUTCOMMANDSYSTEM_H
