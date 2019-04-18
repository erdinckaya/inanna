//
// Created by Erdınc Kaya on 2019-04-18.
//

#ifndef INANNA_COLLISIONSYSTEM_H
#define INANNA_COLLISIONSYSTEM_H


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
            entities.each<Collidable>([&entities, this](entityx::Entity left, Collidable &leftC) {
                entities.each<Collidable>([&left, &leftC, this](entityx::Entity right, Collidable &rightC) {
                    if (left != right && leftC.box.IsIntersect(rightC.box)) {
                        printf("Colliding\n");
                        manager->emit<CollisionEvent>(left, right);
                    }
                });
            });
        }

    private:
        entityx::EventManager *manager;
    };
}

#endif //INANNA_COLLISIONSYSTEM_H
