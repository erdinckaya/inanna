//
// Created by misterdortnal on 22.01.2019.
//

#ifndef INANNA_SPRITEANIMATIONRENDERSYSTEM_H
#define INANNA_SPRITEANIMATIONRENDERSYSTEM_H

#include <entityx/System.h>
#include "../../Graphics/Graphics.h"
#include "../Components/SpriteAnimation.h"
#include "../../UI/Components/Position.h"

namespace Inanna {
    struct SpriteRenderSystem : entityx::System<SpriteRenderSystem> {
        explicit SpriteRenderSystem(Graphics *graphics) : graphics(graphics) {}

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Position, SpriteAnimation>(
                    [this, dt](entityx::Entity entity, Position &position, SpriteAnimation &animation) {
                        auto keyFrame = animation.KeyFrame();
                        Rectf clip = {0, 0, keyFrame.w, keyFrame.h};
                        Rectf pos = {position.global.x, position.global.y, keyFrame.w, keyFrame.h};
                        graphics->DrawTexture(keyFrame, clip, pos, 0, Vecf(1, 1));
                        animation.time += dt;
                    });
        }

        Graphics *graphics;
    };
}

#endif //INANNA_SPRITEANIMATIONRENDERSYSTEM_H
