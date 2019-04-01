//
// Created by Erdınc Kaya on 2019-04-01.
//

#ifndef INANNA_DAMAGE_H
#define INANNA_DAMAGE_H

#include <entityx/Entity.h>

namespace Inanna {
    struct Damage {
        explicit Damage(entityx::Entity entity, const float &damage, const bool &source) : entity(entity),
                                                                                           damage(damage),
                                                                                           source(source) {}

        entityx::Entity entity;
        bool source;
        float damage;
    };
}
#endif //INANNA_DAMAGE_H
