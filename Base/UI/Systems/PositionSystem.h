//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_POSITIONSYSTEM_H
#define INANNA_POSITIONSYSTEM_H


#include <entityx/System.h>
#include "../Components/Renderable.h"
#include "../Components/Position.h"
#include "../Components/Widget.h"

namespace Inanna {

    class PositionSystem : public entityx::System<PositionSystem> {
    public:
        explicit PositionSystem() = default;

        void CalculateRealPosition(entityx::Entity entity, Position &position) {
            auto isWidget = entity.has_component<Widget>();
            if (isWidget) {
                auto widget = entity.component<Widget>();
                if (widget->HasParent()) {
                    position.global = position.position + widget->parent.component<Position>()->global;
                } else {
                    position.global = position.position;
                }
            }
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Position>([this](entityx::Entity entity, Position &position){
                auto renderable = entity.component<Renderable>();
                CalculateRealPosition(entity, position);
                renderable->pos = position.global;
            });
        }
    };
}


#endif //INANNA_POSITIONSYSTEM_H
