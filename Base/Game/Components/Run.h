//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_RUN_H
#define INANNA_RUN_H

#include <entityx/config.h>
#include "../../Util/Math/Vec2.h"
#include "../../../Assets/AnimationData.h"

namespace Inanna {
    struct Run {
        explicit Run(const Vecf &direction, int speed, const SpriteAnimData &animData) : direction(direction),
                                                                                                   speed(speed),
                                                                                                   animData(animData),
                                                                                                   time(0) {}


        int speed;
        Vecf direction;
        float time;
        SpriteAnimData animData;

        REFLECT()
    };
}
#endif //INANNA_RUN_H
