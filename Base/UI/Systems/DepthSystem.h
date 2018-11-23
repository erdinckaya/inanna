//
// Created by Erdınc Kaya on 23.11.2018.
//

#ifndef INANNA_DEPTHSYSTEM_H
#define INANNA_DEPTHSYSTEM_H

#include <entityx/System.h>
#include "../Components/Widget.h"
#include "../Components/Root.h"

namespace Inanna {
    class DepthSystem : public entityx::System<DepthSystem> {
    public:
        explicit DepthSystem() = default;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Root>([this](entityx::Entity entity, Root &root) {
                AssignDepth(entity, Veci(0, 0));
            });
        }

        void AssignDepth(entityx::Entity entity, const Veci &depth) {
            auto widget = entity.component<Widget>();
            widget->depth = depth;
            int size = widget->ChildCount();
            for (int i = 0; i < size; ++i) {
                AssignDepth(widget->GetChild(i), Veci(depth.x + 1, i));
            }
        }
    };
}

#endif //INANNA_DEPTHSYSTEM_H
