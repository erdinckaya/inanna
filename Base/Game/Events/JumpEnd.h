//
// Created by misterdortnal on 31.01.2019.
//

#ifndef INANNA_JUMPENDED_H
#define INANNA_JUMPENDED_H

#include <entityx/Entity.h>

namespace Inanna {
    struct JumpEnd {
        explicit JumpEnd(entityx::Entity entity) : entity(entity) {}

        entityx::Entity entity;
    };
}

#endif //INANNA_JUMPENDED_H
