//
// Created by Erdınc Kaya on 2019-03-25.
//

#ifndef INANNA_HITEND_H
#define INANNA_HITEND_H

#include <entityx/Entity.h>

namespace Inanna {
    struct HitEnd {
        explicit HitEnd(entityx::Entity entity) : entity(entity) {}

        entityx::Entity entity;
    };
}
#endif //INANNA_HITEND_H
