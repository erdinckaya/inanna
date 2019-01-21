//
// Created by Erdınc Kaya on 2019-01-18.
//

#ifndef INANNA_SPRITEANIMATIONFACTORY_H
#define INANNA_SPRITEANIMATIONFACTORY_H

#include <entityx/entityx.h>
#include "../../Assets/AnimationData.h"

namespace Inanna {
    class SpriteAnimationFactory : public entityx::EntityX {
    public:
        explicit SpriteAnimationFactory() = default;

        entityx::Entity CreateAnimation(const SpriteAnimData &animation);
    };
}

#endif //INANNA_SPRITEANIMATIONFACTORY_H
