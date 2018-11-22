//
// Created by Erdınc Kaya on 22.11.2018.
//

#ifndef INANNA_RENDERSYSTEM_H
#define INANNA_RENDERSYSTEM_H

#include <entityx/System.h>
#include "../../Graphics/Graphics.h"
#include "../Components/Renderable.h"

namespace Inanna {
    class RenderSystem : public entityx::System<RenderSystem> {
    public:
        explicit RenderSystem(Graphics* graphics) : graphics(graphics) {}

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Renderable>([this](entityx::Entity entity, Renderable &renderable){
                Rectf clip = {
                        0.0f, 0.0f,
                        renderable.target.w, renderable.target.h
                };

                Rectf pos = {
                        0.0f, 0.0f,
                        renderable.target.w, renderable.target.h
                };
                graphics->DrawTexture(renderable.target, clip, pos, renderable.rotation, renderable.scale);
            });
        }

    private:
        Graphics* graphics;
    };
}

#endif //INANNA_RENDERSYSTEM_H
