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
                auto pPos = player.component<Position>();
                auto rPos = rival.component<Position>();

                auto old = player.component<Facing>()->left;
                player.component<Facing>()->left = pPos->position.x < rPos->position.x;
                rival.component<Facing>()->left = !player.component<Facing>()->left;
            }
        }
    };
}

#endif //INANNA_SPRITEFACINGSYSTEM_H
