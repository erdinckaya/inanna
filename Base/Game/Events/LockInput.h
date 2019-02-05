//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_LOCKINPUT_H
#define INANNA_LOCKINPUT_H


#include <entityx/Entity.h>

namespace Inanna {
    struct LockInput {
        explicit LockInput(entityx::Entity entity, bool value) : entity(entity), value(value) {}

        entityx::Entity entity;
        bool value;
    };
}

#endif //INANNA_LOCKINPUT_H
