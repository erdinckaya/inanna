//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_POSITIONSYSTEM_H
#define INANNA_POSITIONSYSTEM_H


#include <entityx/System.h>
#include "../Components/Renderable.h"
#include "../Components/Position.h"

namespace Inanna {

    class PositionSystem : public entityx::System<PositionSystem> {
    public:
        explicit PositionSystem() = default;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Position>([this](entityx::Entity entity, Position &position){
                auto renderable = entity.component<Renderable>();
                renderable->pos = position.position;
            });
        }
    };
}


#endif //INANNA_POSITIONSYSTEM_H
