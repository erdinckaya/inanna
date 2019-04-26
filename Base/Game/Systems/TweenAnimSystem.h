//
// Created by Erdınc Kaya on 2019-04-26.
//

#ifndef INANNA_TWEENANIMSYSTEM_H
#define INANNA_TWEENANIMSYSTEM_H


#include <entityx/System.h>
#include "../Util/Chrono.h"
#include "../Components/TweenAnim.h"

namespace Inanna {
    struct TweenAnimSystem : public entityx::System<TweenAnimSystem>, entityx::Receiver<TweenAnimSystem> {

        explicit TweenAnimSystem() : manager(nullptr) {}

        void configure(entityx::EventManager &events) override {
            manager = &events;
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<TweenAnim>([this, dt](entityx::Entity entity, TweenAnim &tweenAnim) {
                if (tweenAnim.destroy) {
                    printf("Entity deleted\n");
                    entity.destroy();
                    return;
                }

                if (tweenAnim.tween.progress() == 0.0f) {
                    tweenAnim.OnStart();
                }

                tweenAnim.tween.step((int32_t) dt);

                if (tweenAnim.tween.progress() >= 1.0f) {
                    tweenAnim.destroy = true;
                    tweenAnim.OnComplete();
                }
            });
        }

    private:
        entityx::EventManager *manager;
    };
}


#endif //INANNA_TWEENANIMSYSTEM_H
