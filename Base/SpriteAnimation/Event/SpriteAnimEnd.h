//
// Created by misterdortnal on 31.01.2019.
//

#ifndef INANNA_SPRITEANIMEND_H
#define INANNA_SPRITEANIMEND_H


#include <entityx/Entity.h>

namespace Inanna {

    struct SpriteAnimEnd {
        explicit SpriteAnimEnd(entityx::Entity entity) : entity(entity) {}

        entityx::Entity entity;

    };

}

#endif //INANNA_SPRITEANIMEND_H
