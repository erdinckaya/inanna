//
// Created by Erdınc Kaya on 2019-02-27.
//

#ifndef INANNA_SPRITEGIZMOSYSTEM_H
#define INANNA_SPRITEGIZMOSYSTEM_H


#include <entityx/System.h>
#include "../../UI/Components/Position.h"
#include "../../Game/Components/Gizmo.h"
#include "../Components/SpriteAnimation.h"
#include "../../World.h"

namespace Inanna {
    // Pivots are bottom left for anims
    struct SpriteGizmoSystem : public entityx::System<SpriteGizmoSystem> {

        explicit SpriteGizmoSystem(Graphics* graphics) : graphics(graphics) {}

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Position, SpriteAnimation, Facing>(
                    [this](entityx::Entity entity, Position &position, SpriteAnimation &sprite, Facing &facing) {
                        auto image = sprite.KeyFrame();
                        if (image.hitRect != Rectf(0, 0, 0, 0)) {

                            auto x = image.hitRect.x;
                            auto y = image.hitRect.y;
                            if (!facing.left) {
                                x = (position.global.x + sprite.Size().x) - (image.hitRect.x + image.hitRect.w) - position.global.x;
                            }

                            Rectf pos = Rectf(position.global + Vecf(x, y), Vecf(image.hitRect.w, image.hitRect.h));
                            sprite.hitbox = pos;

                            graphics->DrawRect(pos, {1, 0, 0, 1}, 1);

                            Rectf bound = Rectf(position.global, Vecf(image.w, image.h));
                            graphics->DrawRect(bound, {0, 0, 1, 1}, 2);
                        } else {
                            sprite.hitbox = Rectf(0, 0, 0, 0);
                        }

                        if (HAS_COMP(entity, Gizmo)) {
                            auto gizmo = COMP(entity, Gizmo);
                            if (gizmo->drawBoundingBox) {
                                Rectf bound = Rectf(position.global, Vecf(image.w, image.h));
                                graphics->DrawRect(bound, {0, 0, 1, 1}, 2);
                            }
                        }
                    });
        }

        Graphics *graphics;
    };
}

#endif //INANNA_SPRITEGIZMOSYSTEM_H
