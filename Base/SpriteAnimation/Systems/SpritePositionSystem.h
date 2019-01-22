//
// Created by misterdortnal on 22.01.2019.
//

#ifndef INANNA_SPRITEPOSITIONSYSTEM_H
#define INANNA_SPRITEPOSITIONSYSTEM_H

#include <entityx/System.h>
#include "../../UI/Components/Position.h"
#include "../Components/SpriteAnimation.h"

namespace Inanna {
    // Pivots are bottom left for anims
    struct SpritePositionSystem : public entityx::System<SpritePositionSystem> {

        explicit SpritePositionSystem() : GROUND(0, SCREEN_HEIGHT) {}

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            entities.each<Position, SpriteAnimation>(
                    [this](entityx::Entity entity, Position &position, SpriteAnimation &sprite) {
                        auto image = sprite.KeyFrame();
                        Vecf size = Vecf(0, image.h);
                        auto pos = Vecf(position.position.x, -position.position.y);
                        position.global = GROUND + pos - size;
                    });
        }

        const Vecf GROUND;
    };
}


#endif //INANNA_SPRITEPOSITIONSYSTEM_H
