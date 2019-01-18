//
// Created by Erdınc Kaya on 2019-01-18.
//

#ifndef INANNA_SPRITEANIMATION_H
#define INANNA_SPRITEANIMATION_H

#include <entityx/config.h>
#include "../../../Assets/AnimationData.h"
#include "SpriteAnimationState.h"

namespace Inanna {
    struct SpriteAnimation {

        explicit SpriteAnimation(const SpriteAnimData *animData) : animData(animData), frameIndex(0), reverse(false),
                                                                   time(0), loop(false), loopCount(-1),
                                                                   state(SpriteAnimationState::Start),
                                                                   killAtFinish(false), pingpong(false) {}

        const ImageAsset KeyFrame() {
            return animData->KeyFrame(frameIndex);
        }

        const SpriteAnimData *animData;
        int frameIndex;
        bool reverse;
        entityx::TimeDelta time;
        bool loop;
        bool pingpong;
        int loopCount;
        SpriteAnimationState state;
        bool killAtFinish;
    };
}

#endif //INANNA_SPRITEANIMATION_H
