//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_ROLLEND_H
#define INANNA_ROLLEND_H


#include <entityx/Entity.h>

namespace Inanna {
    struct RollEnd {
        explicit RollEnd(entityx::Entity entity) : entity(entity) {}

        entityx::Entity entity;
    };
}

#endif //INANNA_ROLLEND_H
