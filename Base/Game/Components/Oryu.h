//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_ORYU_H
#define INANNA_ORYU_H


#include "../Util/Chrono.h"
#include "../../../Assets/AnimationData.h"
#include "../../Util/Math/Vec2.h"

namespace Inanna {
    struct Oryu {
        explicit Oryu(SpriteAnimData animData, const Vecf &direction, int speed) : time(0), speed(speed),
                                                                                   animData(std::move(animData)),
                                                                                   direction(direction) {}

        float time;
        int speed;
        Vecf direction;
        SpriteAnimData animData;

        REFLECT()
    };
}

#endif //INANNA_ORYU_H
