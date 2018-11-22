//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_SCALESYSTEM_H
#define INANNA_SCALESYSTEM_H

#include <entityx/System.h>
#include "../Components/Scalable.h"
#include "../Components/Renderable.h"

namespace Inanna {

    class ScaleSystem : public entityx::System<ScaleSystem> {
    public:
        explicit ScaleSystem() {}

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Scalable>([this](entityx::Entity entity, Scalable &scalable){
                auto renderable = entity.component<Renderable>();
                renderable->scale = scalable.scale;
            });
        }
    };
}

#endif //INANNA_SCALESYSTEM_H
