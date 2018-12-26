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
        explicit MouseInputSystem(): ClickDiff(500), lastMouseDownTime(0) {};

        void configure(entityx::EventManager &events) override {
            clickEntity = entityx::Entity();
            overEntity = entityx::Entity();
            lastMouseDownEntity = entityx::Entity();
            dragEntity = entityx::Entity();
        }


        void SetClickEntity(entityx::Entity &entity) {
            clickEntity = entity;
        }

        void SetOverEntity(entityx::Entity &entity) {
            if (overEntity.valid()) {
                overEntity.component<Widget>()->mouseWidget = false;
            }
            overEntity = entity;
            overEntity.component<Widget>()->mouseWidget = true;
        }

        void ReleaseOverEntity() {
            if (overEntity.valid()) {
                overEntity.component<Widget>()->mouseWidget = false;
            }
            overEntity = entityx::Entity();
        }

        void AssignWidget(entityx::EntityManager &manager, const Vecf &mouse) {
            std::vector<entityx::Entity> entities;
            manager.each<Renderable, Interaction>(
                    [&](entityx::Entity entity, Renderable &renderable, Interaction &interaction) {
//                        Rectf box = {renderable.pos.x, renderable.pos.y, renderable.size.x, renderable.size.x};
                        Rectf box = renderable.renderContext;
//                        printf("Box x: %f, y: %f, w: %f, h: %f\n", box.x, box.y, box.w, box.h);
                        bool isPointIn = box.IsPointIn(mouse) && interaction.mouse;
                        if (isPointIn) {
                            entities.emplace_back(entity);
                        }
                    });

            // No UI clicked!
            if (entities.empty()) {
                clickEntity = entityx::Entity();
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
                    SetClickEntity(entities[i]);
                }
            }

            // Clear it
            entities.clear();
        }

        void AssignOverWidget(entityx::EntityManager &manager, const Vecf &mouse) {
            std::vector<entityx::Entity> entities;
            manager.each<Renderable, Interaction>(
                    [&](entityx::Entity entity, Renderable &renderable, Interaction &interaction) {
//                        Rectf box = {renderable.pos.x, renderable.pos.y, renderable.size.x, renderable.size.x};
                        Rectf box = renderable.renderContext;
                        bool isPointIn = box.IsPointIn(mouse) && interaction.mouse;
                        if (isPointIn) {
                            entities.emplace_back(entity);
                        }
                    });

            // No UI clicked!
            if (entities.empty()) {
                ReleaseOverEntity();
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
                    SetOverEntity(entities[i]);
                }
            }

            // Clear it
            entities.clear();
        }

        void ProcessMouseButtonInput(MouseButton &button, entityx::EventManager &events) {
            mouseButtonEvent = button.event;

            if (clickEntity.valid() && mouseButtonEvent.button == SDL_BUTTON_LEFT) {
                if (mouseButtonEvent.type == SDL_MOUSEBUTTONUP) {
                    events.emit<MouseUpEvent>(clickEntity, mouseButtonEvent);

                    auto diff = mouseButtonEvent.timestamp - lastMouseDownTime;
                    if (clickEntity == lastMouseDownEntity && diff <= ClickDiff) {
                        events.emit<MouseClickEvent>(clickEntity, mouseButtonEvent);
                    }

                    if (dragEntity.valid() && dragEntity.has_component<MouseDrag>()) {
                        events.emit<MouseDragEndEvent>(dragEntity, mouseMotionEvent);
                        dragEntity.invalidate();
                    }
                    clickEntity.invalidate();
                } else {
                    lastMouseDownEntity = clickEntity;
                    lastMouseDownTime = mouseButtonEvent.timestamp;

                    if (!dragEntity.valid() && clickEntity.has_component<MouseDrag>()) {
                        dragEntity = clickEntity;
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

            if (clickEntity.valid()) {
                // Search for scrollview.
                entityx::Entity ent = clickEntity;
                while (ent.valid()) {
                    if (dragEntity != ent && ent.has_component<MouseDrag>()) {
                        events.emit<MouseDragEvent>(ent, mouseMotionEvent);
                    }

                    if (ent.has_component<Widget>()) {
                        ent = ent.component<Widget>()->parent;
                    } else {
                        ent.invalidate();
                    }
                }
            }
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<MouseButton>([&](entityx::Entity entity, MouseButton &event) {
                AssignWidget(entities, Vecf(event.event.x, event.event.y));
                ProcessMouseButtonInput(event, events);
                entity.destroy();
            });


            entities.each<MouseMotion>([&](entityx::Entity entity, MouseMotion &event) {
                AssignOverWidget(entities, Vecf(event.event.x, event.event.y));
                ProcessMouseMotionInput(event, events);
                entity.destroy();
            });

            entities.each<MouseWheel>([&](entityx::Entity entity, MouseWheel &event) {
                entity.destroy();
            });

            if (mouseButtonEvent.type == SDL_MOUSEBUTTONDOWN && clickEntity.valid()) {
                events.emit<MouseDownEvent>(clickEntity, mouseButtonEvent);
            }
        }

    private:
        entityx::Entity clickEntity;
        entityx::Entity overEntity;
        entityx::Entity lastMouseDownEntity;
        entityx::Entity dragEntity;
        SDL_MouseButtonEvent mouseButtonEvent{};
        SDL_MouseMotionEvent mouseMotionEvent{};
        Uint32 lastMouseDownTime;

        const Uint32 ClickDiff;
    };
}

#endif //INANNA_MOUSEINPUTSYSTEM_H
