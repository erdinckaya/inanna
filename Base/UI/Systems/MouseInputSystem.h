//
// Created by Erdınc Kaya on 23.11.2018.
//

#ifndef INANNA_MOUSEINPUTSYSTEM_H
#define INANNA_MOUSEINPUTSYSTEM_H


#include <entityx/System.h>
#include "../../Util/Math/Rect.h"
#include "../Components/MouseButton.h"
#include "../Components/MouseWheel.h"
#include "../Components/MouseMotion.h"
#include "../Components/Renderable.h"
#include "../Components/Widget.h"
#include "../Components/Interaction.h"
#include "../MouseEventComponents/MouseDrag.h"
#include "../MouseEvents/MouseDownEvent.h"
#include "../MouseEvents/MouseUpEvent.h"
#include "../MouseEvents/MouseClickEvent.h"
#include "../MouseEvents/MouseDragEvent.h"
#include "../MouseEvents/MouseDragEndEvent.h"
#include "../MouseEvents/MouseDragStartEvent.h"

namespace Inanna {

    class MouseInputSystem : public entityx::System<MouseInputSystem> {
    public:
        explicit MouseInputSystem(): ClickDiff(100), lastMouseDownTime(0) {};

        void configure(entityx::EventManager &events) override {
            current = entityx::Entity();
            lastMouseDownEntity = entityx::Entity();
            dragEntity = entityx::Entity();
        }


        void AssignWidget(entityx::EntityManager &manager, const Vecf &mouse) {
            std::vector<entityx::Entity> entities;
            manager.each<Renderable, Interaction>(
                    [&](entityx::Entity entity, Renderable &renderable, Interaction &interaction) {
                        Rectf box = {renderable.pos.x, renderable.pos.y, renderable.size.x, renderable.size.x};
                        bool isPointIn = box.IsPointIn(mouse) && interaction.mouse;
                        if (isPointIn) {
                            entities.emplace_back(entity);
                        }
                    });

            // No UI clicked!
            if (entities.empty()) {
                current = entityx::Entity();
                return;
            }

            // Find Deepest Widget
            int x = -1;
            int size = static_cast<int>(entities.size());
            for (int i = 0; i < size; ++i) {
                auto depth = entities[i].component<Widget>()->depth;
                if (depth.x > x) {
                    x = depth.x;
                }
            }

            // Prune Others
            for (int i = size - 1; i > -1; --i) {
                auto depth = entities[i].component<Widget>()->depth;
                if (depth.x < x) {
                    entities.erase(entities.begin() + i);
                }
            }

            // Find Last render order.
            int y = -1;
            size = static_cast<int>(entities.size());
            for (int i = 0; i < size; ++i) {
                auto depth = entities[i].component<Widget>()->depth;
                if (depth.y > y) {
                    y = depth.y;
                }
            }

            // Assign the entity;
            for (int i = 0; i < size; ++i) {
                auto depth = entities[i].component<Widget>()->depth;
                if (depth.x == x && depth.y == y) {
                    current = entities[i];
                }
            }

            // Clear it
            entities.clear();
        }

        void ProcessMouseButtonInput(MouseButton &button, entityx::EventManager &events) {
            mouseButtonEvent = button.event;

            if (current.valid()) {
                if (mouseButtonEvent.type == SDL_MOUSEBUTTONUP) {
                    events.emit<MouseUpEvent>(current, mouseButtonEvent);

                    auto diff= mouseButtonEvent.timestamp - lastMouseDownTime;
                    if (current == lastMouseDownEntity && diff <= ClickDiff) {
                        events.emit<MouseClickEvent>(current, mouseButtonEvent);
                    }

                    if (dragEntity.valid() && dragEntity.has_component<MouseDrag>()) {
                        events.emit<MouseDragEndEvent>(dragEntity, mouseMotionEvent);
                        dragEntity.invalidate();
                    }
                } else {
                    lastMouseDownEntity = current;
                    lastMouseDownTime = mouseButtonEvent.timestamp;

                    if (!dragEntity.valid() && current.has_component<MouseDrag>()) {
                        dragEntity = current;
                        events.emit<MouseDragStartEvent>(dragEntity, mouseMotionEvent);
                    }
                }
            }
        }

        void ProcessMouseMotionInput(MouseMotion &motion, entityx::EventManager &events) {
            mouseMotionEvent = motion.event;
            auto diff = Vecf(mouseMotionEvent.xrel, mouseMotionEvent.yrel);
            if (dragEntity.valid() && diff != Vecf(0, 0)) {
                events.emit<MouseDragEvent>(dragEntity, mouseMotionEvent);
            }
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<MouseButton>([&](entityx::Entity entity, MouseButton &event) {
                AssignWidget(entities, Vecf(event.event.x, event.event.y));
                ProcessMouseButtonInput(event, events);
                entity.destroy();
            });


            entities.each<MouseMotion>([&](entityx::Entity entity, MouseMotion &event) {
                ProcessMouseMotionInput(event, events);
                entity.destroy();
            });

            entities.each<MouseWheel>([&](entityx::Entity entity, MouseWheel &event) {
                entity.destroy();
            });

            if (mouseButtonEvent.type == SDL_MOUSEBUTTONDOWN && current.valid()) {
                events.emit<MouseDownEvent>(current, mouseButtonEvent);
            }
        }

    private:
        entityx::Entity current;
        entityx::Entity lastMouseDownEntity;
        entityx::Entity dragEntity;
        SDL_MouseButtonEvent mouseButtonEvent;
        SDL_MouseMotionEvent mouseMotionEvent;
        Uint32 lastMouseDownTime;

        const Uint32 ClickDiff;

    };
}

#endif //INANNA_MOUSEINPUTSYSTEM_H
