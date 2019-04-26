//
// Created by Erdınc Kaya on 2019-03-01.
//

#ifndef INANNA_SPRITEFACINGSYSTEM_H
#define INANNA_SPRITEFACINGSYSTEM_H


#include <entityx/System.h>
#include "../../UI/Components/Position.h"
#include "../../Game/Components/Facing.h"
#include "../../Game/Components/Character.h"
#include "../../Game/Game.h"

namespace Inanna {
    // Pivots are bottom center
    struct SpriteFacingSystem : public entityx::System<SpriteFacingSystem> {

        explicit SpriteFacingSystem() = default;

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            auto player = Game::Instance->Player;
            auto rival = Game::Instance->Rival;
            if (player.valid() && rival.valid()) {
                auto pPos = COMP(player, Position);
                auto rPos = COMP(rival, Position);
                auto pImg = COMP(player, SpriteAnimation)->KeyFrame();
                auto rImg = COMP(rival, SpriteAnimation)->KeyFrame();
                auto pFace = COMP(player, Facing)->left;
                auto rFace = COMP(rival, Facing)->left;


//                auto px = pPos->position.x + pImg.w * (pFace ? 0.5f : -0.5f);
//                auto rx = rPos->position.x + rImg.w * (rFace ? 0.5f : -0.5f);

                auto px = pPos->position.x;
                auto rx = rPos->position.x;

                COMP(player, Facing)->left = px < rx;
                COMP(rival, Facing)->left = !(COMP(player, Facing)->left);

                auto left = COMP(player, Facing)->left;
                if (pFace != left) {

                    COMP(player, Position)->position.x += left ? -pImg.w : pImg.w;
                    COMP(rival, Position)->position.x += !left ? -rImg.w : rImg.w;
                }
            }
        }
    };
}

#endif //INANNA_SPRITEFACINGSYSTEM_H
