//
// Created by Erdınc Kaya on 2018-12-21.
//

#ifndef INANNA_SCROLLVIEWERSYSTEM_H
#define INANNA_SCROLLVIEWERSYSTEM_H

#include <entityx/System.h>

#include "../Components/Widget.h"
#include "../Components/Root.h"
#include "../Components/Position.h"
#include "../Components/Sizable.h"
#include "../Widgets/ScrollViewer.h"
#include "../MouseEventComponents/MouseDrag.h"

namespace Inanna {

    class ScrollViewerSystem : public entityx::System<ScrollViewerSystem> {
    public:
        explicit ScrollViewerSystem() = default;

        void AssignDragEvents(entityx::Entity entity) {
            if (!entity.has_component<MouseDrag>()) {
                entity.assign<MouseDrag>([](entityx::Entity entity, SDL_MouseMotionEvent event) {
                    // TODO Move widgets interms of directions
                });
            }
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<ScrollViewer>([this](entityx::Entity entity, ScrollViewer &scrollViever){
                AssignDragEvents(entity);
            });
        }
    };
}

#endif //INANNA_SCROLLVIEWERSYSTEM_H
