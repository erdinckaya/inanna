//
// Created by misterdortnal on 23.01.2019.
//

#ifndef INANNA_MOVECHARACTER_H
#define INANNA_MOVECHARACTER_H

#include <entityx/config.h>
#include "../../Util/Math/Vec2.h"

namespace Inanna {
    struct MoveCharacter {
        explicit MoveCharacter(const Vecf &direction, int speed) : direction(direction), speed(speed), time(0) {}


        int speed;
        Vecf direction;
        float time;

        REFLECT()
    };
}
#endif //INANNA_MOVECHARACTER_H
