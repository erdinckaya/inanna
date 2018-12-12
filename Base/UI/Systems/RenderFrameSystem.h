//
// Created by Erdınc Kaya on 2018-12-12.
//

#ifndef INANNA_RENDERFRAMESYSTEM_H
#define INANNA_RENDERFRAMESYSTEM_H

#include <entityx/System.h>
#include "../Components/Widget.h"
#include "../Components/Root.h"
#include "../Components/Sizable.h"
#include "../../Util/Math/Rect.h"
#include "../Components/RenderFrame.h"
#include "../Components/Position.h"
#include "../Components/Renderable.h"

namespace Inanna {
    class RenderFrameSystem : public entityx::System<RenderFrameSystem> {
    public:
        explicit RenderFrameSystem() = default;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Root>([this](entityx::Entity entity, Root &root) {
                AssignRenderFrame(entity, false, Rectf(0, 0, 0, 0));
            });
        }

        void AssignRenderFrame(entityx::Entity entity, bool hasFrame, Rectf frame) {
            auto widget = entity.component<Widget>();
            if (hasFrame) {
                if (entity.has_component<Renderable>()) {
                    auto renderable = entity.component<Renderable>();
                    renderable->hasFrame = true;
                    renderable->frame = frame;
                }
            }

            if (entity.has_component<RenderFrame>()) {
                hasFrame = true;

                auto position = entity.component<Position>();
                frame = Rectf(position->global.x + entity.component<RenderFrame>()->frame.x,
                              position->global.y + entity.component<RenderFrame>()->frame.y,
                              entity.component<RenderFrame>()->frame.w,
                              entity.component<RenderFrame>()->frame.h);
            }

            int size = widget->ChildCount();
            for (int i = 0; i < size; ++i) {
                auto child = widget->GetChild(i);
                AssignRenderFrame(child, hasFrame, frame);
            }
        }
    };
}

#endif //INANNA_RENDERFRAMESYSTEM_H
