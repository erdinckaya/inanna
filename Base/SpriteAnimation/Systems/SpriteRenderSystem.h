//
// Created by misterdortnal on 22.01.2019.
//

#ifndef INANNA_SPRITEANIMATIONRENDERSYSTEM_H
#define INANNA_SPRITEANIMATIONRENDERSYSTEM_H

#include <entityx/System.h>
#include "../../Graphics/Graphics.h"
#include "../Components/SpriteAnimation.h"
#include "../../UI/Components/Position.h"
#include "../../Game/Components/Facing.h"
#include "../Components/SpriteZ.h"

#include "../../../ThirdParty/boolinq.h"

using namespace boolinq;

namespace Inanna {
    struct SpriteRenderSystem : entityx::System<SpriteRenderSystem> {
        explicit SpriteRenderSystem(Graphics *graphics) : graphics(graphics) {}

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::vector<entityx::Entity> sprites;
            entities.each<Position, Facing, SpriteAnimation, SpriteZ>(
                    [this, &sprites](entityx::Entity entity, Position &position, Facing &facing,
                                     SpriteAnimation &animation, SpriteZ zorder) {
                        sprites.push_back(entity);
                    });

            sprites = from(sprites).orderBy([](const entityx::Entity &ent) {
                entityx::Entity e = ent;
                return e.component<SpriteZ>()->z;
            }).reverse().toVector();
            const int size = static_cast<const int>(sprites.size());
            for (int i = 0; i < size; ++i) {
                auto ent = sprites[i];
                auto position = ent.component<Position>();
                auto facing = ent.component<Facing>();
                auto animation = ent.component<SpriteAnimation>();

                auto keyFrame = animation->KeyFrame();
                Rectf clip = {0, 0, keyFrame.w, keyFrame.h};
                Rectf pos = {position->global.x, position->global.y, keyFrame.w, keyFrame.h};

                graphics->DrawTexture(keyFrame, clip, pos, 0, Vecf(1, 1), !facing->left, false);
                animation->time += dt;
            }
        }

        Graphics *graphics;
    };
}

#endif //INANNA_SPRITEANIMATIONRENDERSYSTEM_H
