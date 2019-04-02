//
// Created by misterdortnal on 02.04.2019.
//

#ifndef INANNA_DAMAGEEND_H
#define INANNA_DAMAGEEND_H


#include <entityx/Entity.h>

namespace Inanna {
    struct DamageEnd {
        explicit DamageEnd(entityx::Entity entity) : entity(entity) {}

        entityx::Entity entity;
    };
}

#endif //INANNA_DAMAGEEND_H
