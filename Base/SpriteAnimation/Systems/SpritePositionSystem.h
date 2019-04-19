//
// Created by misterdortnal on 22.01.2019.
//

#ifndef INANNA_SPRITEPOSITIONSYSTEM_H
#define INANNA_SPRITEPOSITIONSYSTEM_H

#include <unordered_set>

#include <entityx/System.h>
#include "../../UI/Components/Position.h"
#include "../Components/SpriteAnimation.h"
#include "../../World.h"
#include "../../Game/Components/Facing.h"
#include "../../Game/Components/JumpCharacter.h"
#include "../../Game/Components/JumpBack.h"
#include "../../Game/Components/MoveCharacter.h"
#include "../../Game/Components/Run.h"
#include "../../Game/Components/Facing.h"
#include "../../Game/Components/Collidable.h"
#include "../../Game/Components/CharacterState.h"
#include "../../Game/Util/CharacterBehaivour.h"


namespace Inanna {
    // Pivots are bottom left for anims
    struct SpritePositionSystem : public entityx::System<SpritePositionSystem> {

        explicit SpritePositionSystem() : GROUND(0, SCREEN_HEIGHT) {}

        static Rectf GetBoundingBox(entityx::Entity ent) {
            auto position = COMP(ent, Position);
            auto anim = COMP(ent, SpriteAnimation);
            auto face = COMP(ent, Facing);

            const Vecf ground = Vecf(0, SCREEN_HEIGHT);
            auto image = anim->KeyFrame();
            Vecf size = Vecf(0, image.h);
            auto pos = Vecf(position->position.x, -position->position.y);
            return Rectf(ground + pos - size, Vecf(image.w, image.h) + anim->boundingBoxOffset);
        }

        static void AdjustPositions(entityx::Entity &left, Collidable &colL, entityx::Entity &right, Collidable &colR,
                                    Rectf &intersect) {

            auto posL = COMP(left, Position);
            auto posR = COMP(right, Position);
            auto faceL = COMP(left, Facing);
            auto faceR = COMP(right, Facing);

            if (IS_PUSHING(left)) {
                Adjust(posL, posR, colL.box, colR.box, faceL);
            } else if (IS_PUSHING(right)) {
                Adjust(posR, posL, colR.box, colL.box, faceR);
            } else {
                if (HAS_COMP(left, CharacterState) && HAS_COMP(left, CharacterState)) {
                    auto lState = COMP(left, CharacterState);
                    auto rState = COMP(right, CharacterState);
                    if (lState->state == CharacterBehaviour::Idle && rState->state == CharacterBehaviour::Idle) {
                        Adjust(posL, posR, colL.box, colR.box, faceL);
                    }
                }
            }
        }

        static void Adjust(entityx::ComponentHandle<Position> &posL, const entityx::ComponentHandle<Position> &posR, const Rectf &boxL,
                    const Rectf &boxR, const entityx::ComponentHandle<Facing> &faceL) {
            if (faceL->left) {
                if (posL->position.x >= posR->position.x + boxR.w * 0.5f) { // jump other size
                    posL->position.x = posR->position.x + boxR.w;
                } else {
                    posL->position.x = posR->position.x - boxL.w;
                }
            } else {
                if (posL->position.x <= posR->position.x + boxR.w * 0.5f) { // jump other size
                    posL->position.x = posR->position.x - boxL.w;
                } else {
                    posL->position.x = posR->position.x + boxR.w;
                }
            }
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::unordered_set<entityx::Entity> entSet;
            entities.each<Collidable>([&entities, this, &entSet](entityx::Entity entL, Collidable &colL) {
                colL.box = GetBoundingBox(entL);
                entities.each<Collidable>([&entL, &colL, this, &entSet](entityx::Entity entR, Collidable &colR) {
                    colR.box = GetBoundingBox(entR);
                    auto pair = Rectf::GetIntersect(colL.box, colR.box);
                    if (entL != entR && !(HAS_KEY(entSet, entL) || HAS_KEY(entSet, entR)) && pair.first) {
                        entSet.insert(entL);
                        printf("1312312\n");
                        AdjustPositions(entL, colL, entR, colR, pair.second);
                    }
                });
            });


            entities.each<Position, SpriteAnimation, Facing>(
                    [this](entityx::Entity entity, Position &position, SpriteAnimation &sprite, Facing &facing) {
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
