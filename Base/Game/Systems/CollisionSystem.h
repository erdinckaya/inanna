//
// Created by Erdınc Kaya on 2019-04-18.
//

#ifndef INANNA_COLLISIONSYSTEM_H
#define INANNA_COLLISIONSYSTEM_H

#include <unordered_set>

#include <entityx/System.h>
#include "../../UI/Components/Position.h"
#include "../../Util/SpriteMacro.h"
#include "../Components/Collidable.h"
#include "../Events/CollisionEvent.h"

namespace Inanna {
    struct CollisionSystem : public entityx::System<CollisionSystem>, entityx::Receiver<CollisionSystem> {

        explicit CollisionSystem() : manager(nullptr) {}

        void configure(entityx::EventManager &events) override {
            manager = &events;
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
            std::unordered_set<entityx::Entity> entSet;
            entities.each<Collidable>([&entities, this, &entSet](entityx::Entity entL, Collidable &colL) {
                colL.box = SpritePositionSystem::GetBoundingBox(entL);
                entities.each<Collidable>([&entL, &colL, this, &entSet](entityx::Entity entR, Collidable &colR) {
                    colR.box = SpritePositionSystem::GetBoundingBox(entR);
                    if (entL != entR && !(HAS_KEY(entSet, entL) || HAS_KEY(entSet, entR)) && colL.box.IsIntersect(colR.box)) {
                        entSet.insert(entL);
//                        manager->emit<CollisionEvent>(entL, entR);
                    }
                });
            });
        }


    private:
        entityx::EventManager *manager;
    };
}

#endif //INANNA_COLLISIONSYSTEM_H
