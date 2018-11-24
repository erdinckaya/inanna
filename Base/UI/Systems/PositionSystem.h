//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_POSITIONSYSTEM_H
#define INANNA_POSITIONSYSTEM_H


#include <entityx/System.h>
#include "../Components/Renderable.h"
#include "../Components/Position.h"
#include "../Components/Widget.h"
#include "../Components/Root.h"

namespace Inanna {

    class PositionSystem : public entityx::System<PositionSystem> {
    public:
        explicit PositionSystem() = default;

        void CalculateRealPosition(entityx::Entity entity) {
            auto isRoot = entity.has_component<Root>();
            auto isWidget = entity.has_component<Widget>();
            if (isWidget) {
                auto widget = entity.component<Widget>();
                auto position = entity.component<Position>();
                if (widget->HasParent()) {
                    position->global = position->position + widget->parent.component<Position>()->global;
                } else {
                    position->global = position->position;
                }
                entity.component<Renderable>()->pos = position->global;
                auto size = widget->ChildCount();
                for (int i = 0; i < size; ++i) {
                    auto child = widget->GetChild(i);
                    CalculateRealPosition(child);
                }
            }
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Root>([this](entityx::Entity entity, Root &position) {
                auto renderable = entity.component<Root>();
                CalculateRealPosition(entity);
            });
        }
    };
}


#endif //INANNA_POSITIONSYSTEM_H
