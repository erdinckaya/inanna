//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_MOVEEND_H
#define INANNA_MOVEEND_H

#include <entityx/Entity.h>

namespace Inanna {
    struct MoveEnd {
        explicit MoveEnd(entityx::Entity entity) : entity(entity) {}

        entityx::Entity entity;
    };
}

#endif //INANNA_MOVEEND_H
