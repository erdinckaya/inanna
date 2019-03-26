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

            printf("State is %s\n", cmd.state._to_string());
            SpriteAnimData animData = AnimationData::KYO_LITTLE_FIST;
            bool canHit = true;
            switch (cmd.state) {
                case CharacterBehaviour::LittleFist:
                    animData = AnimationData::KYO_LITTLE_FIST;
                    break;
                case CharacterBehaviour::BigFist:
                    animData = AnimationData::KYO_BIG_FIST;
                    break;
                case CharacterBehaviour::LittleKick:
                    animData = AnimationData::KYO_LITTLE_KICK;
                    break;
                case CharacterBehaviour::BigKick:
                    animData = AnimationData::KYO_BIG_KICK;
                    break;

//                case CharacterBehaviour::CrouchLittleFist:
//                    animData = AnimationData::KYO_CROUCH_LITTLE_FIST;
//                    break;
//                case CharacterBehaviour::CrouchBigFist:
//                    animData = AnimationData::KYO_CROUCH_BIG_FIST;
//                    break;
//                case CharacterBehaviour::CrouchLittleKick:
//                    animData = AnimationData::KYO_CROUCH_LITTLE_KICK;
//                    break;
//                case CharacterBehaviour::CrouchBigKick:
//                    animData = AnimationData::KYO_CROUCH_BIG_KICK;
//                    break;
//
//
//                case CharacterBehaviour::JumpLittleFist:
//                    animData = AnimationData::KYO_JUMP_LITTLE_FIST;
//                    break;
//                case CharacterBehaviour::JumpBigFist:
//                    animData = AnimationData::KYO_JUMP_BIG_FIST;
//                    break;
//                case CharacterBehaviour::JumpLittleKick:
//                    animData = AnimationData::KYO_JUMP_LITTLE_KICK;
//                    break;
//                case CharacterBehaviour::JumpBigKick:
//                    animData = AnimationData::KYO_JUMP_BIG_KICK;
//                    break;
                default:
                    canHit = false;
                    break;
            }

            if (canHit) {
                cmd.character.assign<Hit>(cmd.userKey.key, animData);
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
