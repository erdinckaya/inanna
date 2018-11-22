//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_ROTATIONSYSTEM_H
#define INANNA_ROTATIONSYSTEM_H


#include <entityx/System.h>
#include "../Components/Renderable.h"
#include "../Components/Rotation.h"

namespace Inanna {

    class RotationSystem : public entityx::System<RotationSystem> {
    public:
        explicit RotationSystem() {}

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Rotation>([this](entityx::Entity entity, Rotation &rotation){
                auto renderable = entity.component<Renderable>();
                renderable->rotation = rotation.rotation;
            });
        }
    };
}

#endif //INANNA_ROTATIONSYSTEM_H
