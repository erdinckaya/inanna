//
// Created by misterdortnal on 22.01.2019.
//

#ifndef INANNA_SPRITEPOSITIONSYSTEM_H
#define INANNA_SPRITEPOSITIONSYSTEM_H

#include <entityx/System.h>
#include "../../UI/Components/Position.h"
#include "../Components/SpriteAnimation.h"
#include "../../World.h"
#include "../../Game/Components/Facing.h"
#include "../../Game/Components/Collidable.h"

namespace Inanna {
    // Pivots are bottom left for anims
    struct SpritePositionSystem : public entityx::System<SpritePositionSystem> {

        explicit SpritePositionSystem() : GROUND(0, SCREEN_HEIGHT) {}

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Position, SpriteAnimation, Facing>(
                    [this](entityx::Entity entity, Position &position, SpriteAnimation &sprite, Facing &facing) {
                        auto image = sprite.KeyFrame();
                        Vecf size = Vecf(facing.left ? 0 : image.w, image.h);
                        auto pos = Vecf(position.position.x, -position.position.y);
                        position.global = GROUND + pos - size;

                        if (HAS_COMP(entity, Collidable)) {
                            auto collide = COMP(entity, Collidable);
                            collide->box = Rectf(Vecf(position.global.x, position.global.y), sprite.Size());
                        }
                    });
        }

        const Vecf GROUND;
    };
}


#endif //INANNA_SPRITEPOSITIONSYSTEM_H
