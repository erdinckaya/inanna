//
// Created by Erdınc Kaya on 2019-04-18.
//

#ifndef INANNA_COLLISIONEVENT_H
#define INANNA_COLLISIONEVENT_H


#include <entityx/Entity.h>

namespace Inanna {
    struct CollisionEvent {
        explicit CollisionEvent(entityx::Entity left, entityx::Entity right) : left(left), right(right) {}

        entityx::Entity left;
        entityx::Entity right;
    };
}

#endif //INANNA_COLLISIONEVENT_H
