//
// Created by Erdınc Kaya on 2019-03-28.
//

#ifndef INANNA_SPRITEFORCEKEYFRAME_H
#define INANNA_SPRITEFORCEKEYFRAME_H


#include <entityx/Entity.h>

namespace Inanna {

    struct SpriteForceKeyFrame {
        explicit SpriteForceKeyFrame(entityx::Entity entity, int index) : entity(entity), index(index) {}

        entityx::Entity entity;
        int index;
    };

}


#endif //INANNA_SPRITEFORCEKEYFRAME_H
