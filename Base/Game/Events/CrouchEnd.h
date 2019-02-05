//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_CROUCHEND_H
#define INANNA_CROUCHEND_H


#include <entityx/Entity.h>

namespace Inanna {
    struct CrouchEnd {
        explicit CrouchEnd(entityx::Entity entity) : entity(entity) {}

        entityx::Entity entity;
    };
}

#endif //INANNA_CROUCHEND_H
