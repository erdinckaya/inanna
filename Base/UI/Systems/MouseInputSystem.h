//
// Created by Erdınc Kaya on 23.11.2018.
//

#ifndef INANNA_MOUSEINPUTSYSTEM_H
#define INANNA_MOUSEINPUTSYSTEM_H


#include <entityx/System.h>
#include "../Components/MouseButton.h"
#include "../Components/MouseWheel.h"
#include "../Components/MouseMotion.h"
#include "../Components/Renderable.h"
#include "../Components/Widget.h"
#include "../Components/Interaction.h"
#include "../../Util/Math/Rect.h"

namespace Inanna {

    class MouseInputSystem : public entityx::System<MouseInputSystem> {
    public:
        void configure(entityx::EventManager &events) override {
            current = entityx::Entity();
        }

    public:
        explicit MouseInputSystem() = default;

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

        void ProcessMouseButtonInput(MouseButton &button) {
            switch ((int) button.event.button) {
                case SDL_BUTTON_LEFT: {
                    if (button.event.type == SDL_MOUSEBUTTONDOWN) {
                        if (current.valid()) {
                            printf("Clicked Widget is %s\n", current.component<Renderable>()->target.id);
//                            current.component<Interaction>()->mouse = false;
                        } else {
                            printf("NonValid Click\n");
                        }
                    }
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    break;
                }
                default:
                    break;
            }
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<MouseButton>([&](entityx::Entity entity, MouseButton &event) {
                AssignWidget(entities, Vecf(event.event.x, event.event.y));
                ProcessMouseButtonInput(event);
                entity.destroy();
            });

            entities.each<MouseMotion>([&](entityx::Entity entity, MouseMotion &event) {
                entity.destroy();
            });

            entities.each<MouseWheel>([&](entityx::Entity entity, MouseWheel &event) {
                entity.destroy();
            });
        }

    private:
        entityx::Entity current;
    };
}

#endif //INANNA_MOUSEINPUTSYSTEM_H
