//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_RENDERSYSTEM_H
#define INANNA_RENDERSYSTEM_H

#include <entityx/System.h>
#include "../../Graphics/Graphics.h"
#include "../Components/Renderable.h"
#include "../Components/Root.h"
#include "../Events/ClearAllEvent.h"
#include "../Components/Widget.h"
#include "../Components/Interaction.h"

namespace Inanna {
    class RenderSystem : public entityx::System<RenderSystem>, public entityx::Receiver<RenderSystem> {
    public:
        explicit RenderSystem(Graphics *graphics) : graphics(graphics), clearAll(false) {}

        void configure(entityx::EventManager &events) override {
            events.subscribe<ClearAllEvent>(*this);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            if (clearAll) {
                entities.each<Renderable>([this](entityx::Entity entity, Renderable &renderable) {
                    entity.destroy();
                });
                clearAll = false;
                return;
            }

            entities.each<Root>([this](entityx::Entity entity, Root &root) {
                Traverse(entity);
            });
        }

        void Traverse(entityx::Entity entity) {
            auto interaction = entity.component<Interaction>();
            if (interaction->visible) {
                Render(*entity.component<Renderable>());
                auto isWidget = entity.has_component<Widget>();
                if (isWidget) {
                    auto widget = entity.component<Widget>();

                    int size = widget->ChildCount();
                    for (int i = 0; i < size; ++i) {
                        Traverse(widget->GetChild(i));
                    }
                }
            }
        }

        void Render(const Renderable &renderable) const {
            Rectf clip = {0, 0, renderable.target.w, renderable.target.h};
            Rectf pos = {renderable.pos.x, renderable.pos.y, renderable.size.x, renderable.size.y};
            if (renderable.target.valid()) {
                graphics->DrawTexture(renderable.target, clip, pos, renderable.rotation, renderable.scale);
            }
        }

        void receive(const ClearAllEvent &event) {
            clearAll = true;
        }


    private:
        Graphics *graphics;
        bool clearAll;
    };
}

#endif //INANNA_RENDERSYSTEM_H
