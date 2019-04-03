#include <utility>

//
// Created by Erdınc Kaya on 2019-04-01.
//

#ifndef INANNA_DAMAGE_H
#define INANNA_DAMAGE_H

#include <entityx/Entity.h>

namespace Inanna {
    struct Damage {
        explicit Damage(entityx::Entity source, entityx::Entity destination, const float &damage, SpriteAnimData animData, float startPos) :
                damage(damage), source(source), animData(std::move(animData)), totalTime(0),
                pushBackDistance(100), pushBackTime(0.3f), startPos(startPos) {}

        entityx::Entity source;
        entityx::Entity destination;
        SpriteAnimData animData;
        float damage;
        float totalTime;
        float pushBackDistance;
        float pushBackTime;
        float startPos;
    };
}
#endif //INANNA_DAMAGE_H
