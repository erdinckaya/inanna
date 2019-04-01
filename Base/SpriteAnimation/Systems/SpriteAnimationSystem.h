//
// Created by Erdınc Kaya on 2019-01-18.
//

#ifndef INANNA_SPRITEANIMATIONSYSTEM_H
#define INANNA_SPRITEANIMATIONSYSTEM_H

#include <entityx/System.h>
#include "../Components/SpriteAnimation.h"
#include "../../Graphics/Graphics.h"
#include "../Components/Time.h"
#include "../../Util/SpriteMacro.h"
#include "../Event/SpriteIndex.h"
#include "../Event/SpriteAnimEnd.h"
#include "../Components/SpriteLoop.h"
#include "../Event/SpriteForceKeyFrame.h"

#include <queue>

namespace Inanna {
    struct SpriteAnimationSystem : public entityx::System<SpriteAnimationSystem>, entityx::Receiver<SpriteAnimationSystem> {

        explicit SpriteAnimationSystem() = default;

        void configure(entityx::EventManager &events) override {
            events.subscribe<SpriteForceKeyFrame>(*this);
        }

        SpriteAnimationState Next(entityx::Entity entity, SpriteAnimation *animation) {
            animation->time = 0;
            if (animation->state == SpriteAnimationState::Finished) {
                return static_cast<SpriteAnimationState>(animation->state);
            }

            if (animation->reverse) {
                animation->frameIndex--;
            } else {
                animation->frameIndex++;
            }

            if (entity.has_component<SpriteLoop>()) { ;
                animation->frameIndex = std::max(entity.component<SpriteLoop>()->start,
                                                 std::min(animation->frameIndex, entity.component<SpriteLoop>()->end));
            }

            const int frameSize = static_cast<int>(animation->animData.keyFrames.size());
            int limit = animation->reverse ? -1 : frameSize;
            if (animation->frameIndex == limit) {
                if (animation->loop) {
                    animation->state = SpriteAnimationState::Animating;
                } else if (animation->pingpong) {
                    animation->reverse = !animation->reverse;
                    animation->frameIndex = animation->reverse ? frameSize - 1 : 0;
                    animation->pingpong = false;
                } else {
                    animation->state = SpriteAnimationState::Finished;
                }
            } else {
                animation->state = SpriteAnimationState::Animating;
            }

            if (entity.has_component<SpriteLoop>()) {
                auto start = entity.component<SpriteLoop>()->start;
                auto end = entity.component<SpriteLoop>()->end;
                auto size = end - start + 1;

                animation->frameIndex += size;
                animation->frameIndex %= size;
                animation->frameIndex += start;
            } else {
                animation->frameIndex += frameSize;
                animation->frameIndex %= frameSize;
                if (animation->stayAtLastFrame) {
                    animation->frameIndex = animation->LastFrame();
                }
            }


            return static_cast<SpriteAnimationState>(animation->state);
        }

        void FireSpriteEvent(entityx::Entity entity, entityx::EventManager &manager, int index) {
            if (entity.has_component<SpriteIndex>()) {
                if (entity.component<SpriteIndex>()->index == index) {
                    INANNA_REMOVE_COMPONENT(entity, SpriteIndex);
                    manager.emit<SpriteIndex>(entity, index);
                }
            }
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<SpriteAnimation>([this, dt, &events](entityx::Entity entity, SpriteAnimation &animation) {
                double speed = 1000.0 / animation.animData.speed;
                bool isKilled = false;
                if (animation.time >= speed) {
                    auto state = Next(entity, &animation);
                    FireSpriteEvent(entity, events, animation.frameIndex);
                    if (state == SpriteAnimationState::Finished) {
                        INANNA_COMMAND_EXECUTED(entity);
                        events.emit<SpriteAnimEnd>(entity);
                        if (animation.killAtFinish) {
                            isKilled = true;
                            entity.destroy();
                        }
                    }
                }
            });
        }

        void receive(const SpriteForceKeyFrame &spriteForceKeyFrame) {
            SpriteForceKeyFrame event = spriteForceKeyFrame;
            event.entity.component<SpriteAnimation>()->frameIndex = event.index;
        }
    };
}

#endif //INANNA_SPRITEANIMATIONSYSTEM_H
