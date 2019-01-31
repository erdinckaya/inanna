//
// Created by misterdortnal on 31.01.2019.
//

#ifndef INANNA_SPRITEINDEXEVENT_H
#define INANNA_SPRITEINDEXEVENT_H

#include <entityx/Entity.h>

namespace Inanna {

    struct SpriteIndex {
        explicit SpriteIndex(entityx::Entity entity, int index) : entity(entity), index(index) {}

        entityx::Entity entity;
        int index;
    };

}

#endif //INANNA_SPRITEINDEXEVENT_H
