#include <utility>

//
// Created by Erdınc Kaya on 2019-01-18.
//

#ifndef INANNA_SPRITEANIMATION_H
#define INANNA_SPRITEANIMATION_H

#include "../../../Assets/AnimationData.h"
#include "SpriteAnimationState.h"
#include "../../Util/Math/Vec2.h"
#include "../../../ThirdParty/Signals/Signal.h"


namespace Inanna {
    struct SpriteAnimation {

        explicit SpriteAnimation(SpriteAnimData animData) : animData(std::move(animData)), frameIndex(0),
                                                            reverse(false),
                                                            time(0), loop(false),
                                                            state(SpriteAnimationState::Start),
                                                            killAtFinish(false), pingpong(false),
                                                            stayAtLastFrame(false), hitbox(0, 0, 0, 0),
                                                            boundingBoxOffset(10, 10) {}

        const ImageAsset KeyFrame() {
            return animData.keyFrames[frameIndex];
        }

        const int LastFrame() {
            return animData.keyFrames.size() - 1;
        }

        const Vecf Size() {
            float w = -1;
            float h = -1;
            const int size = static_cast<const int>(animData.keyFrames.size());
            for (int i = 0; i < size; ++i) {
                auto keyFrame = animData.keyFrames[i];
                if (w < keyFrame.w) {
                    w = keyFrame.w;
                }

                if (h < keyFrame.h) {
                    h = keyFrame.h;
                }
            }

            return Vecf(w, h);
        }

        SpriteAnimData animData;
        int frameIndex;
        bool reverse;
        float time;
        bool loop;
        bool pingpong;
        int state;
        bool killAtFinish;
        bool stayAtLastFrame;

        Rectf hitbox;

        Vecf boundingBoxOffset;

        REFLECT()
    };
}

#endif //INANNA_SPRITEANIMATION_H
