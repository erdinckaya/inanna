#include <utility>

#include <utility>

//
// Created by Erdınc Kaya on 2019-04-26.
//

#ifndef INANNA_TWEENANIM_H
#define INANNA_TWEENANIM_H

#include <tween.h>
#include <functional>

namespace Inanna {

    struct TweenAnim {
        explicit TweenAnim(tweeny::tween<float> tween) : tween(std::move(tween)), destroy(false) {}

        explicit TweenAnim(tweeny::tween<float> tween, std::function<void(void)> start, std::function<void(void)> end)
                : tween(std::move(tween)), destroy(false), onStart(std::move(start)), onComplete(std::move(end)) {}

        TweenAnim &OnStart(std::function<void(void)> callback) {
            onStart = std::move(callback);
            return *this;
        }

        void OnStart() {
            if (onStart) {
                onStart();
            }
        }

        TweenAnim &OnComplete(std::function<void(void)> callback) {
            onComplete = std::move(callback);
            return *this;
        }

        void OnComplete() {
            if (onComplete) {
                onComplete();
            }
        }

        tweeny::tween<float> tween;
        bool destroy;

    private:
        std::function<void(void)> onStart;
        std::function<void(void)> onComplete;
    };
}

#endif //INANNA_TWEENANIM_H
