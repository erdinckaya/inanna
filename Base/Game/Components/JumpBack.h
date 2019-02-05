#include <utility>

//
// Created by Erdınc Kaya on 2019-02-05.
//

#ifndef INANNA_JUMPBACK_H
#define INANNA_JUMPBACK_H

#include "../Util/Chrono.h"
#include "../../../Assets/AnimationData.h"
#include "../../Util/Math/Vec2.h"

namespace Inanna {
    struct JumpBack {
        explicit JumpBack(SpriteAnimData animData, const Vecf &direction, int speed) : time(0), speed(speed),
                                                                                       animData(std::move(animData)),
                                                                                       direction(direction) {}

        float time;
        int speed;
        Vecf direction;
        SpriteAnimData animData;
    };
}
#endif //INANNA_JUMPBACK_H
