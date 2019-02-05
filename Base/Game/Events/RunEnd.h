//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_RUNEND_H
#define INANNA_RUNEND_H

#include <entityx/Entity.h>

namespace Inanna {
    struct RunEnd {
        explicit RunEnd(entityx::Entity entity) : entity(entity) {}

        entityx::Entity entity;
    };
}
#endif //INANNA_RUNEND_H
