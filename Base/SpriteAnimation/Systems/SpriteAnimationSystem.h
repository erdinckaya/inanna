//
// Created by Erdınc Kaya on 2019-01-18.
//

#ifndef INANNA_SPRITEANIMATIONSYSTEM_H
#define INANNA_SPRITEANIMATIONSYSTEM_H

#include <entityx/System.h>
#include "../Components/SpriteAnimation.h"
#include "../../Graphics/Graphics.h"

namespace Inanna {
    struct SpriteAnimationSystem : public entityx::System<SpriteAnimationSystem> {

        explicit SpriteAnimationSystem() = default;

        SpriteAnimationState Next(SpriteAnimation* animation) {
            animation->time = 0;
            if (animation->state == SpriteAnimationState::Finished) {
                return animation->state;
            }

            if (animation->reverse) {
                animation->frameIndex--;
            } else {
                animation->frameIndex++;
            }

            const int frameSize = static_cast<int>(animation->animData.keyFrames.size());
            int limit = animation->reverse ? -1 : frameSize;
            if (animation->frameIndex == limit) {
                if (animation->loop) {
                    animation->state = SpriteAnimationState::Animating;
                } else if (animation->pingpong)  {
                    animation->reverse = !animation->reverse;
                    animation->frameIndex = animation->reverse ? frameSize - 1 : 0;
                    animation->pingpong = false;
                } else {
                    animation->state = SpriteAnimationState::Finished;
                }
            } else {
                animation->state = SpriteAnimationState::Animating;
            }

            animation->frameIndex += frameSize;
            animation->frameIndex %= frameSize;

            return animation->state;
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<SpriteAnimation>([this, dt](entityx::Entity entity, SpriteAnimation &animation) {
                double speed = 1000.0 / animation.animData.speed;
                bool isKilled = false;
                if (animation.time >= speed) {
                    auto state = Next(&animation);
                    if (state == SpriteAnimationState::Finished && animation.killAtFinish) {
                        isKilled = true;
                        entity.destroy();
                    }
                }
            });
        }

    };
}

#endif //INANNA_SPRITEANIMATIONSYSTEM_H
