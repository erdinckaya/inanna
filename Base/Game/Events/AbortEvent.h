//
// Created by Erdınc Kaya on 2019-03-13.
//

#ifndef INANNA_ABORTEVENT_H
#define INANNA_ABORTEVENT_H


#include <entityx/Entity.h>

namespace Inanna {
    struct AbortEvent {
        explicit AbortEvent(entityx::Entity entity) : entity(entity) {}

        entityx::Entity entity;
    };
}


#endif //INANNA_ABORTEVENT_H
