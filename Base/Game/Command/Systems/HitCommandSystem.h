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
#include "../../Components/Collidable.h"
#include "../../Events/HitEnd.h"

using namespace boolinq;

namespace Inanna {
    struct HitCommandSystem : public entityx::System<HitCommandSystem>, entityx::Receiver<HitCommandSystem> {

        void configure(entityx::EventManager &events) override {
            manager = &events;
            events.subscribe<HitEnd>(*this);
            events.subscribe<AbortEvent>(*this);
        }

        void CharacterHit(HitCommand &cmd) {
            if (cmd.character.has_component<Hit>()) {
                return;
            }

            SpriteAnimData animData = AnimationData::KYO_LITTLE_FIST;
            bool canHit = true;
            bool stayAtLastFrame = false;
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

                case CharacterBehaviour::CrouchLittleFist:
                    stayAtLastFrame = true;
                    animData = AnimationData::KYO_CROUCH_LITTLE_FIST;
                    break;
                case CharacterBehaviour::CrouchBigFist:
                    stayAtLastFrame = true;
                    animData = AnimationData::KYO_CROUCH_BIG_FIST;
                    break;
                case CharacterBehaviour::CrouchLittleKick:
                    stayAtLastFrame = true;
                    animData = AnimationData::KYO_CROUCH_LITTLE_KICK;
                    break;
                case CharacterBehaviour::CrouchBigKick:
                    stayAtLastFrame = true;
                    animData = AnimationData::KYO_CROUCH_BIG_KICK;
                    break;


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
                cmd.character.component<CharacterState>()->lock = true;
                INANNA_REMOVE_COMPONENT(cmd.character, Collidable)
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
                auto characterState = event.entity.component<CharacterState>();
                characterState->lock = false;
                if (!KeyInput::Instance.IsKeyHeld(GameKey::Down)) {
                    INANNA_REPLACE_SPRITE_ANIM_WITH_LOOP(event.entity, AnimationData::KYO_IDLE);
                } else {
                    INANNA_REPLACE_SPRITE_ANIM_IF_NOT(event.entity, AnimationData::KYO_CROUCH);
                    manager->emit<SpriteForceKeyFrame>(event.entity, AnimationData::KYO_CROUCH.keyFrames.size() - 1);
                }
                INANNA_REMOVE_COMPONENT(event.entity, Hit)
                INANNA_REPLACE_COMPONENT(event.entity, Collidable)
            }
        }

        void receive(const AbortEvent &abortEvent) {
            AbortEvent event = abortEvent;
            if (event.entity.has_component<Hit>() && event.level > 0) {

            }
        }

    private:
        entityx::EventManager *manager;
    };
}
#endif //INANNA_HITCOMMANDSYSTEM_H
