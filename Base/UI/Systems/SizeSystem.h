//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_SIZESYSTEM_H
#define INANNA_SIZESYSTEM_H


#include <entityx/System.h>
#include "../Components/Sizable.h"
#include "../Components/Renderable.h"

namespace Inanna {

    class SizeSystem : public entityx::System<SizeSystem> {
    public:
        explicit SizeSystem() = default;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Sizable>([this](entityx::Entity entity, Sizable &sizable){
                auto renderable = entity.component<Renderable>();
                if (renderable->target.valid() && sizable.nativeSize) {
                    sizable.size = Vecf(renderable->target.w, renderable->target.h);
                }
                renderable->size = sizable.size;
            });
        }
    };
}

#endif //INANNA_SIZESYSTEM_H
