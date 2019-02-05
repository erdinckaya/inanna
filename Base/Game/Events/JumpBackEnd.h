//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_JUMPBACKEND_H
#define INANNA_JUMPBACKEND_H

#include <entityx/Entity.h>

namespace Inanna {
    struct JumpBackEnd {
        explicit JumpBackEnd(entityx::Entity entity) : entity(entity) {}

        entityx::Entity entity;
    };
}
#endif //INANNA_JUMPBACKEND_H
