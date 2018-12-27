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
#include "../Widgets/ScrollBar.h"

namespace Inanna {

    class ScrollViewerSystem : public entityx::System<ScrollViewerSystem> {
    public:
        explicit ScrollViewerSystem() = default;

        void CalculateValues(entityx::Entity entity, const Veci &mouse) {
            auto content = entity.component<Widget>()->GetChild(0);
            auto contentSize = content.component<Sizable>();
            auto renderContext = entity.component<Renderable>()->renderContext;
            auto scrollBar = entity.component<ScrollBar>();
            auto direction = scrollBar->direction;


            auto gapVertical = contentSize->size.y - renderContext.y;
            bool canScrollVertical = gapVertical >= 0.0f;

            auto gapHorizontal = contentSize->size.x - renderContext.x;
            bool canScrollHorizontal = gapVertical >= 0.0f;

            switch (direction) {

                case Horizontal: {
                    if (canScrollHorizontal) {
                        scrollBar->value = Vecf(0, scrollBar->value.y + mouse.y);
                    }
                    else {
                        scrollBar->value = Vecf(0, 0);
                    }

                    break;
                }
                case Vertical: {
                    if (canScrollVertical) {
                        scrollBar->value = Vecf(scrollBar->value.x + mouse.x, 0);
                    } else {
                        scrollBar->value = Vecf(0, 0);
                    }
                    break;
                }
                case HorizontalVertical: {
                    if (canScrollHorizontal) {
                        scrollBar->value = Vecf(0, scrollBar->value.y + mouse.y);
                    }
                    else {
                        scrollBar->value = Vecf(0, scrollBar->value.y);
                    }

                    if (canScrollVertical) {
                        scrollBar->value = Vecf(scrollBar->value.x + mouse.x, 0);
                    } else {
                        scrollBar->value = Vecf(0, scrollBar->value.x);
                    }

                    if (!canScrollHorizontal && canScrollVertical) {
                        scrollBar->value = Vecf(0, 0);
                    }
                    break;
                }
            }

            float rX = 0.0f;
            if (canScrollHorizontal) {
                rX = scrollBar->value.x / gapHorizontal;
                rX = std::max(std::min(rX, 1.0f), 0.0f);
            }

            float rY = 0.0f;
            if (canScrollHorizontal) {
                rY = scrollBar->value.y / gapVertical;
                rY = std::max(std::min(rY, 1.0f), 0.0f);
            }

            scrollBar->ratio = Vecf(rX, rY);
        }

        void AssignDragEvents(entityx::Entity entity) {
            if (!entity.has_component<MouseDrag>()) {
                entity.assign<MouseDrag>([this](entityx::Entity entity, SDL_MouseMotionEvent event) {
                    // TODO Move widgets interms of directions
                    printf("Mouse diff %d\n", event.y);
                    CalculateValues(entity, Veci(event.xrel, event.yrel));
                });
            }
        }

        void Scroll(entityx::Entity entity) {
            auto content = entity.component<Widget>()->GetChild(0);
            auto scrollBar = entity.component<ScrollBar>();
            auto position = content.component<Position>();
            float x = scrollBar->ratio;

        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<ScrollViewer>([this](entityx::Entity entity, ScrollViewer &scrollViever) {
                AssignDragEvents(entity);
                Scroll(entity);
            });
        }
    };
}

#endif //INANNA_SCROLLVIEWERSYSTEM_H
