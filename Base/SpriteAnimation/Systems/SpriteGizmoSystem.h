//
// Created by Erdınc Kaya on 2019-02-27.
//

#ifndef INANNA_SPRITEGIZMOSYSTEM_H
#define INANNA_SPRITEGIZMOSYSTEM_H


#include <entityx/System.h>
#include "../../UI/Components/Position.h"
#include "../Components/SpriteAnimation.h"
#include "../../World.h"

namespace Inanna {
    // Pivots are bottom left for anims
    struct SpriteGizmoSystem : public entityx::System<SpriteGizmoSystem> {

        explicit SpriteGizmoSystem(Graphics* graphics) : graphics(graphics) {}

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Position, SpriteAnimation>(
                    [this](entityx::Entity entity, Position &position, SpriteAnimation &sprite) {
                        auto image = sprite.KeyFrame();
                        if (image.hitRect != Rectf(0, 0, 0, 0)) {

                            Rectf pos = Rectf(position.global + Vecf(image.hitRect.x, image.hitRect.y),
                                              Vecf(image.hitRect.w, image.hitRect.h));
                            graphics->DrawRect(pos, {1, 0, 0, 1}, 1);

                            Rectf bound = Rectf(position.global, sprite.Size());
                            graphics->DrawRect(bound, {0, 0, 1, 1}, 2);
                        }

                    });
        }

        Graphics *graphics;
    };
}

#endif //INANNA_SPRITEGIZMOSYSTEM_H
