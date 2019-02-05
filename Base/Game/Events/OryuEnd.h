//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_ORYUEND_H
#define INANNA_ORYUEND_H

#include <entityx/Entity.h>

namespace Inanna {
    struct OryuEnd {
        explicit OryuEnd(entityx::Entity entity) : entity(entity) {}

        entityx::Entity entity;
    };
}

#endif //INANNA_ORYUEND_H
